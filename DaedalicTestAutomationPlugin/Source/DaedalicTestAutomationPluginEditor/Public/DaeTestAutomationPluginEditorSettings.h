#pragma once

#include <CoreMinimal.h>
#include <UObject/Object.h>
#include "DaeTestAutomationPluginEditorSettings.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(
    FDaeTestAutomationPluginEditorSettingsTestMapPathChangedSignature, const FString&);

/** Custom settings for this plugin. */
UCLASS(config = EditorPerProjectUserSettings)
class UDaeTestAutomationPluginEditorSettings : public UObject
{
    GENERATED_BODY()

public:
    /** Path to look for test maps in. */
    UPROPERTY(config, EditAnywhere)
    FString TestMapPath;

    UDaeTestAutomationPluginEditorSettings();

    virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;

    /** Event when the path to look for test maps in has changed. */
    FDaeTestAutomationPluginEditorSettingsTestMapPathChangedSignature OnTestMapPathChanged;
};
