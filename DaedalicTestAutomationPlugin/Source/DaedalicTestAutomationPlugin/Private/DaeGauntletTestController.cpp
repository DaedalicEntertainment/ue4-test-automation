#include "DaeGauntletTestController.h"
#include "Kismet/GameplayStatics.h"
#include "DaeGauntletStates.h"
#include "DaeTestAutomationPluginSettings.h"
#include "DaeTestLogCategory.h"
#include "DaeTestSuiteActor.h"
#include <AssetRegistryModule.h>
#include <EngineUtils.h>
#include <Engine/AssetManager.h>

void UDaeGauntletTestController::OnInit()
{
    Super::OnInit();

    // Get tests path.
    const UDaeTestAutomationPluginSettings* TestAutomationPluginSettings =
        GetDefault<UDaeTestAutomationPluginSettings>();

    UE_LOG(LogDaeTest, Log, TEXT("Discovering tests from: %s"),
           *TestAutomationPluginSettings->TestMapPath);

    // Build list of tests (based on FAutomationEditorCommonUtils::CollectTestsByClass).
    FAssetRegistryModule& AssetRegistryModule =
        FModuleManager::LoadModuleChecked<FAssetRegistryModule>(TEXT("AssetRegistry"));
    TArray<FAssetData> AssetDataArray;

    AssetRegistryModule.Get().SearchAllAssets(true);
    AssetRegistryModule.Get().GetAssetsByClass(UWorld::StaticClass()->GetFName(), AssetDataArray);

    const FString PatternToCheck =
        FString::Printf(TEXT("/%s/"), *TestAutomationPluginSettings->TestMapPath);

    for (auto ObjIter = AssetDataArray.CreateConstIterator(); ObjIter; ++ObjIter)
    {
        const FAssetData& AssetData = *ObjIter;

        FString Filename = FPackageName::LongPackageNameToFilename(AssetData.ObjectPath.ToString());

        if (Filename.Contains(*PatternToCheck))
        {
            FName MapName = AssetData.AssetName;
            MapNames.Add(MapName);

            UE_LOG(LogDaeTest, Log, TEXT("Discovered test: %s"), *MapName.ToString());
        }
    }

    GetGauntlet()->BroadcastStateChange(FDaeGauntletStates::Initialized);
}

void UDaeGauntletTestController::OnPostMapChange(UWorld* World)
{
    Super::OnPostMapChange(World);

    UE_LOG(LogDaeTest, Log, TEXT("UDaeGauntletTestController::OnPostMapChange - World: %s"),
           *World->GetName());

    if (GetCurrentState() != FDaeGauntletStates::LoadingNextMap)
    {
        return;
    }

    GetGauntlet()->BroadcastStateChange(FDaeGauntletStates::DiscoveringTests);
}

void UDaeGauntletTestController::OnTick(float TimeDelta)
{
    if (GetCurrentState() == FDaeGauntletStates::Initialized)
    {
        // If this isn't a test map (e.g. immediately after startup), load first test map now.
        if (!MapNames.Contains(FName(*GetCurrentMap())))
        {
            UE_LOG(LogDaeTest, Log,
                   TEXT("FDaeGauntletStates::Initialized - World is not a test world, "
                        "loading first test world."));

            MapIndex = -1;
            LoadNextTestMap();
            return;
        }
        else
        {
            GetGauntlet()->BroadcastStateChange(FDaeGauntletStates::DiscoveringTests);
        }
    }
    else if (GetCurrentState() == FDaeGauntletStates::LoadingNextMap)
    {
        UE_LOG(LogDaeTest, Log, TEXT("FDaeGauntletStates::LoadingNextMap - Loading map: %s"),
               *MapNames[MapIndex].ToString());

        UGameplayStatics::OpenLevel(this, MapNames[MapIndex]);
    }
    else if (GetCurrentState() == FDaeGauntletStates::DiscoveringTests)
    {
        // Find test suite.
        ADaeTestSuiteActor* TestSuite = nullptr;

        for (TActorIterator<ADaeTestSuiteActor> ActorIt(GetWorld()); ActorIt; ++ActorIt)
        {
            TestSuite = *ActorIt;
        }

        if (!IsValid(TestSuite))
        {
            UE_LOG(LogDaeTest, Error,
                   TEXT("FDaeGauntletStates::DiscoveringTests - No "
                        "DaeGauntletTestSuiteActor "
                        "found."));
            LoadNextTestMap();
            return;
        }

        // Start first test.
        GetGauntlet()->BroadcastStateChange(FDaeGauntletStates::Running);

        TestSuite->OnTestSuiteSuccessful.AddDynamic(
            this, &UDaeGauntletTestController::OnTestSuiteSuccessful);
        TestSuite->OnTestSuiteFailed.AddDynamic(this,
                                                &UDaeGauntletTestController::OnTestSuiteFailed);

        TestSuite->RunAllTests();
    }
}

void UDaeGauntletTestController::LoadNextTestMap()
{
    if (!MapNames.IsValidIndex(MapIndex + 1))
    {
        // All tests finished.
        UE_LOG(LogDaeTest, Log,
               TEXT("UDaeGauntletTestController::LoadNextTestMap - All tests finished."));

        GetGauntlet()->BroadcastStateChange(FDaeGauntletStates::Finished);

        EndTest(0);
        return;
    }

    // Load next test map in next tick. This is to avoid invocation list changes during OnPostMapChange.
    ++MapIndex;
    GetGauntlet()->BroadcastStateChange(FDaeGauntletStates::LoadingNextMap);
}

void UDaeGauntletTestController::OnTestSuiteSuccessful(ADaeTestSuiteActor* TestSuite)
{
    LoadNextTestMap();
}

void UDaeGauntletTestController::OnTestSuiteFailed(ADaeTestSuiteActor* TestSuite)
{
    LoadNextTestMap();
}
