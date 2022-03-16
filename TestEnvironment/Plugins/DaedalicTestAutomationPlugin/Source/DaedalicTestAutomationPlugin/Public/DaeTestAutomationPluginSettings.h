#pragma once

#include <CoreMinimal.h>
#include <UObject/Object.h>
#include "DaeTestAutomationPluginSettings.generated.h"

DECLARE_MULTICAST_DELEGATE(FDaeTestAutomationPluginSettingsTestMapsChangedSignature);

/** Custom settings for this plugin. */
UCLASS(config = Game, defaultconfig)
class DAEDALICTESTAUTOMATIONPLUGIN_API UDaeTestAutomationPluginSettings : public UObject
{
    GENERATED_BODY()

public:
    /** DEPRECATED: Use TestMapFolders instead. */
    UPROPERTY(config)
    FString TestMapPath;

    /** Paths to look for test maps in, relative to the Content root of your project (e.g. Maps/AutomatedTests). */
    UPROPERTY(config, EditAnywhere)
    TArray<FString> TestMapFolders;

    /** Names of additional maps to test. */
    UPROPERTY(config, EditAnywhere)
    TArray<FName> AdditionalTestMaps;

    /** Names of maps to ignore when found in test map folders. */
    UPROPERTY(config, EditAnywhere)
    TArray<FName> IgnoredMaps;

    /** Console variables to set before running batches of tests (e.g. Automation Window, Gauntlet). */
    UPROPERTY(config, EditAnywhere)
    TMap<FString, FString> ConsoleVariables;

    UDaeTestAutomationPluginSettings();

    virtual void PostInitProperties() override;

#if WITH_EDITOR
    virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

    /** Event when the set of test maps has changed. */
    FDaeTestAutomationPluginSettingsTestMapsChangedSignature OnTestMapsChanged;

    /** Checks whether the specified map contains automated tests to run. */
    bool IsTestMap(const FString& FileName, const FName& MapName) const;
};
