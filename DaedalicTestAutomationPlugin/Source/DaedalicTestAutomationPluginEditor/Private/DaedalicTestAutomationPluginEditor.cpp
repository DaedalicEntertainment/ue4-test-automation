// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "IDaedalicTestAutomationPluginEditor.h"
#include <AssetToolsModule.h>
#include <CoreMinimal.h>
#include <IAssetTypeActions.h>
#include <Modules/ModuleManager.h>

class FDaedalicTestAutomationPluginEditor : public IDaedalicTestAutomationPluginEditor
{
public:
    /** IModuleInterface implementation */
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;

private:
    /** Asset catetory for test automation assets. */
    EAssetTypeCategories::Type DaedalicTestAutomationAssetCategory;

    /** Asset type actions registered by this module. */
    TArray<TSharedPtr<IAssetTypeActions>> AssetTypeActions;

    void RegisterAssetTypeAction(class IAssetTools& AssetTools,
                                 TSharedRef<IAssetTypeActions> Action);
};

IMPLEMENT_MODULE(FDaedalicTestAutomationPluginEditor, DaedalicTestAutomationPluginEditor)

void FDaedalicTestAutomationPluginEditor::StartupModule()
{
    // Register asset types.
    IAssetTools& AssetTools =
        FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();

    DaedalicTestAutomationAssetCategory =
        AssetTools.RegisterAdvancedAssetCategory(FName(TEXT("DaedalicTestAutomationPlugin")),
                                                 NSLOCTEXT("DaedalicTestAutomationPlugin",
                                                           "DaedalicTestAutomationAssetCategory",
                                                           "Test Automation"));

    TSharedRef<IAssetTypeActions> TestActorBlueprintAction = MakeShareable(
        new FAssetTypeActions_DaeGauntletTestActorBlueprint(DaedalicTestAutomationAssetCategory));
    RegisterAssetTypeAction(AssetTools, TestActorBlueprintAction);
}

void FDaedalicTestAutomationPluginEditor::ShutdownModule()
{
    // Unregister asset types.
    if (FModuleManager::Get().IsModuleLoaded("AssetTools"))
    {
        IAssetTools& AssetToolsModule =
            FModuleManager::GetModuleChecked<FAssetToolsModule>("AssetTools").Get();
        for (auto& AssetTypeAction : AssetTypeActions)
        {
            if (AssetTypeAction.IsValid())
            {
                AssetToolsModule.UnregisterAssetTypeActions(AssetTypeAction.ToSharedRef());
            }
        }
    }

    AssetTypeActions.Empty();
}

void FDaedalicTestAutomationPluginEditor::RegisterAssetTypeAction(
    class IAssetTools& AssetTools, TSharedRef<IAssetTypeActions> Action)
{
    AssetTools.RegisterAssetTypeActions(Action);
    AssetTypeActions.Add(Action);
}
