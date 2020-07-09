#pragma once

#include "DaeTestActor.h"
#include "DaeTestPerformanceBudgetViolation.h"
#include <CoreMinimal.h>
#include <GameFramework/Pawn.h>
#include "DaeTestPerformanceBudgetActor.generated.h"

class ATargetPoint;
class UAutomationPerformaceHelper;

/** Actor that spawns a DefaultPawn to fly along a pre-defined path through the level and monitor performance. */
UCLASS()
class DAEDALICTESTAUTOMATIONPLUGIN_API ADaeTestPerformanceBudgetActor : public ADaeTestActor
{
    GENERATED_BODY()

public:
    ADaeTestPerformanceBudgetActor(
        const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

    virtual void BeginPlay() override;

    virtual void NotifyOnArrange(UObject* Parameter) override;
    virtual void ReceiveOnAct_Implementation(UObject* Parameter) override;
    virtual void NotifyOnAssert(UObject* Parameter) override;

    virtual void Tick(float DeltaSeconds) override;

    virtual TSharedPtr<FDaeTestResultData> CollectResults() const;
    virtual FDaeTestReportWriterSet GetReportWriters() const;

private:
    /** Targets points to fly through, in order. */
    UPROPERTY(EditInstanceOnly)
    TArray<ATargetPoint*> FlightPath;

    /** Pawn to use for flying through the level. */
    UPROPERTY(EditAnywhere)
    TSubclassOf<APawn> PawnClass;

    /** How long to wait before starting to fly, in seconds. */
    UPROPERTY(EditAnywhere)
    float InitialDelay;

    /** How fast to fly, in cm/s. */
    UPROPERTY(EditAnywhere)
    float FlightSpeed;

    /** Radius around flight path points to consider the point as reached, in cm. */
    UPROPERTY(EditAnywhere)
    float AcceptanceRadius;

    /** How long to wait before starting to measure again after a budget violation, in seconds. */
    UPROPERTY(EditAnywhere)
    float BudgetViolationTimeout;

    /** How long game thread is allowed to take for a single frame, in ms. */
    UPROPERTY(EditAnywhere)
    float GameThreadBudget;

    /** How long draw is allowed to take for a single frame, in ms. */
    UPROPERTY(EditAnywhere)
    float RenderThreadBudget;

    /** How long GPU is allowed to take for a single frame, in ms. */
    UPROPERTY(EditAnywhere)
    float GPUBudget;

    /** Whether performance budget violations should cause a failure item in default test reports. */
    UPROPERTY(EditAnywhere)
    bool bIncludeInDefaultTestReport;

    bool bIsRunning;
    bool bIsRecording;

    int32 CurrentTargetPointIndex;
    TArray<FDaeTestPerformanceBudgetViolation> BudgetViolations;
    float LastBudgetViolationTime;

    void BeginRecording();
    void EndRecording();
    bool ValidatePerformanceCounter(float Time, float Budget, const FString& Name);
};
