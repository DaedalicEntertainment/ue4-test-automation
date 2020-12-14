#include "DaeTestPerformanceBudgetActor.h"
#include "DaeTestAssertBlueprintFunctionLibrary.h"
#include "DaeTestLogCategory.h"
#include "DaeTestPerformanceBudgetResultData.h"
#include "DaeTestReportWriterPerformance.h"
#include <EngineGlobals.h>
#include <RenderCore.h>
#include <UnrealClient.h>
#include <Engine/Engine.h>
#include <Engine/GameViewportClient.h>
#include <Engine/TargetPoint.h>
#include <Engine/World.h>
#include <GameFramework/DefaultPawn.h>
#include <GameFramework/GameModeBase.h>
#include <GameFramework/PlayerController.h>
#include <Kismet/GameplayStatics.h>

#if WITH_ENGINE
// Imported from UnrealClient.cpp.
extern ENGINE_API float GAverageFPS;
#else
float GAverageFPS = 0.0f;
#endif // WITH_ENGINE

ADaeTestPerformanceBudgetActor::ADaeTestPerformanceBudgetActor(
    const FObjectInitializer& ObjectInitializer /*= FObjectInitializer::Get()*/)
{
    PrimaryActorTick.bCanEverTick = true;

    // Set reasonable defaults.
    TimeoutInSeconds = 60.0f * 60.0f;

    PawnClass = ADefaultPawn::StaticClass();

    InitialDelay = 1.0f;
    FlightSpeed = 10.0f;
    AcceptanceRadius = 100.0f;

    BudgetViolationTimeout = 5.0f;

    GameThreadBudget = 20.0f;
    RenderThreadBudget = 20.0f;
    GPUBudget = 20.0f;

    bIncludeInDefaultTestReport = true;
}

void ADaeTestPerformanceBudgetActor::BeginPlay()
{
    Super::BeginPlay();

    bIsRunning = false;
    bIsRecording = false;

    CurrentTargetPointIndex = 0;
    LastBudgetViolationTime = 0.0f;
}

void ADaeTestPerformanceBudgetActor::NotifyOnArrange(UObject* Parameter)
{
    Super::NotifyOnArrange(Parameter);

    // Spawn flying pawn.
    APlayerController* Player = UGameplayStatics::GetPlayerController(this, 0);

    if (FlightPath.Num() <= 0)
    {
        UE_LOG(LogDaeTest, Error, TEXT("FlightPath is empty for %s, won't check performance."),
               *GetName());
        return;
    }

    ATargetPoint* StartingPoint = FlightPath[0];

    FRotator SpawnRotation(ForceInit);
    SpawnRotation.Yaw = StartingPoint->GetActorRotation().Yaw;
    FVector SpawnLocation = StartingPoint->GetActorLocation();
    FTransform SpawnTransform = FTransform(SpawnRotation, SpawnLocation);

    FActorSpawnParameters SpawnInfo;
    SpawnInfo.Instigator = GetInstigator();
    SpawnInfo.ObjectFlags |= RF_Transient; // We never want to save default player pawns into a map

    APawn* Pawn = GetWorld()->SpawnActor<APawn>(PawnClass, SpawnTransform, SpawnInfo);

    if (!IsValid(Pawn))
    {
        UE_LOG(LogDaeTest, Error,
               TEXT("%s was unable to spawn pawn %s at %s, won't check performance."), *GetName(),
               *PawnClass->GetName(), *SpawnTransform.ToString());
        return;
    }

    Player->Possess(Pawn);

    UE_LOG(LogDaeTest, Log, TEXT("%s spawned %s for %s at %s."), *GetName(), *Pawn->GetName(),
           *Player->GetName(), *StartingPoint->GetName());
}

void ADaeTestPerformanceBudgetActor::ReceiveOnAct_Implementation(UObject* Parameter)
{
    bIsRunning = true;
}

void ADaeTestPerformanceBudgetActor::NotifyOnAssert(UObject* Parameter)
{
    Super::NotifyOnAssert(Parameter);

    UDaeTestAssertBlueprintFunctionLibrary::AssertEqualInt32(BudgetViolations.Num(), 0,
                                                             TEXT("Budget Violations"), this);
}

void ADaeTestPerformanceBudgetActor::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    if (!bIsRunning)
    {
        return;
    }

    UWorld* World = GetWorld();

    float Time = World->GetTimeSeconds();

    if (Time < InitialDelay)
    {
        return;
    }

    APlayerController* Player = UGameplayStatics::GetPlayerController(this, 0);
    APawn* Pawn = UGameplayStatics::GetPlayerPawn(this, 0);

    if (!IsValid(Player) || !IsValid(Pawn))
    {
        return;
    }

    // Check if we should start recording (again).
    bool bJustBeganRecording = false;

    if (!bIsRecording
        && (BudgetViolations.Num() == 0 || Time > LastBudgetViolationTime + BudgetViolationTimeout))
    {
        BeginRecording();

        // Need to wait one frame before we got actual data.
        bJustBeganRecording = true;
    }

    if (FlightPath.IsValidIndex(CurrentTargetPointIndex))
    {
        // Follow flight path.
        ATargetPoint* CurrentTargetPoint = FlightPath[CurrentTargetPointIndex];

        FVector ToTargetPoint = CurrentTargetPoint->GetActorLocation() - Pawn->GetActorLocation();
        float Distance = ToTargetPoint.Size();

        if (Distance <= AcceptanceRadius)
        {
            // Point reached!
            UE_LOG(LogDaeTest, Log, TEXT("%s has reached %s."), *GetName(),
                   *CurrentTargetPoint->GetName());
            ++CurrentTargetPointIndex;
        }
        else
        {
            // Move towards next point.
            FVector Direction = ToTargetPoint;
            Direction.Normalize();

            float Scale = FMath::Min(Distance, FlightSpeed * DeltaSeconds);

            Pawn->AddMovementInput(Direction, Scale);

            // Smoothly rotate in movement direction.
            FRotator CurrentRotation = Pawn->GetActorRotation();
            FRotator TargetRotation = Direction.ToOrientationRotator();

            FRotator NewRotation =
                FMath::RInterpTo(CurrentRotation, TargetRotation, DeltaSeconds, 1.0f);

            Pawn->SetActorRotation(NewRotation);
        }

        // Check performance.
        if (bIsRecording && !bJustBeganRecording)
        {
            const FStatUnitData* StatUnitData = World->GetGameViewport()->GetStatUnitData();

            float GameThreadTime = StatUnitData->GameThreadTime;
            float RenderThreadTime = StatUnitData->RenderThreadTime;
            float GPUTime = StatUnitData->GPUFrameTime;

            bool bGameThreadTimeOK =
                ValidatePerformanceCounter(GameThreadTime, GameThreadBudget, TEXT("Game"));
            bool bRenderThreadTimeOK =
                ValidatePerformanceCounter(RenderThreadTime, RenderThreadBudget, TEXT("Draw"));
            bool bGPUThreadTimeOK = ValidatePerformanceCounter(GPUTime, GPUBudget, TEXT("GPU"));

            if (!bGameThreadTimeOK || !bRenderThreadTimeOK || !bGPUThreadTimeOK)
            {
                EndRecording();

                LastBudgetViolationTime = Time;

                FScreenshotRequest::RequestScreenshot(true);

                UE_LOG(LogDaeTest, Log, TEXT("Writing screenshot to: %s"),
                       *FScreenshotRequest::GetFilename());

                // Add budget violation.
                FDaeTestPerformanceBudgetViolation BudgetViolation;

                if (FlightPath.IsValidIndex(CurrentTargetPointIndex - 1))
                {
                    BudgetViolation.PreviousTargetPointName =
                        FlightPath[CurrentTargetPointIndex - 1]->GetName();
                }
                else
                {
                    BudgetViolation.PreviousTargetPointName = TEXT("n/a");
                }

                if (FlightPath.IsValidIndex(CurrentTargetPointIndex))
                {
                    BudgetViolation.NextTargetPointName =
                        FlightPath[CurrentTargetPointIndex]->GetName();
                }
                else
                {
                    BudgetViolation.NextTargetPointName = TEXT("n/a");
                }

                BudgetViolation.CurrentLocation = Pawn->GetActorLocation();
                BudgetViolation.FPS =
                    GAverageFPS > 0.0f ? GAverageFPS : (1.0f / (StatUnitData->FrameTime / 1000.0f));
                BudgetViolation.GameThreadTime = GameThreadTime;
                BudgetViolation.RenderThreadTime = RenderThreadTime;
                BudgetViolation.GPUTime = GPUTime;
                BudgetViolation.ScreenshotPath = FScreenshotRequest::GetFilename();

                BudgetViolations.Add(BudgetViolation);
            }
        }
    }
    else
    {
        SetActorTickEnabled(false);

        UE_LOG(LogDaeTest, Log, TEXT("%s has finished."), *GetName());

        EndRecording();

        FinishAct();
    }
}

TSharedPtr<FDaeTestResultData> ADaeTestPerformanceBudgetActor::CollectResults() const
{
    TSharedPtr<FDaeTestPerformanceBudgetResultData> Results =
        MakeShareable(new FDaeTestPerformanceBudgetResultData());

    Results->BudgetViolations = BudgetViolations;

    return Results;
}

FDaeTestReportWriterSet ADaeTestPerformanceBudgetActor::GetReportWriters() const
{
    FDaeTestReportWriterSet ReportWriters;

    if (bIncludeInDefaultTestReport)
    {
        FDaeTestReportWriterSet DefaultReportWriters = Super::GetReportWriters();
        ReportWriters.Add(DefaultReportWriters);
    }

    ReportWriters.Add(MakeShareable(new FDaeTestReportWriterPerformance()));
    return ReportWriters;
}

void ADaeTestPerformanceBudgetActor::BeginRecording()
{
    UWorld* World = GetWorld();

    // Ensure we're recording engine stats.
    GEngine->SetEngineStat(World, World->GetGameViewport(), TEXT("FPS"), true);
    GEngine->SetEngineStat(World, World->GetGameViewport(), TEXT("Unit"), true);

    bIsRecording = true;
}

void ADaeTestPerformanceBudgetActor::EndRecording()
{
    bIsRecording = false;
}

bool ADaeTestPerformanceBudgetActor::ValidatePerformanceCounter(float Time, float Budget,
                                                                const FString& Name)
{
    if (Time <= Budget)
    {
        return true;
    }

    UE_LOG(LogDaeTest, Warning, TEXT("Performance budget violated: %s - Budget: %f, Time: %f"),
           *Name, Budget, Time);

    return false;
}
