#include "AssetTypeActions_DaeGauntletTestActorBlueprint.h"
#include "DaeGauntletTestActorBlueprint.h"
#include "DaeGauntletTestActorBlueprintFactory.h"

#define LOCTEXT_NAMESPACE "DaedalicTestAutomationPlugin"

FAssetTypeActions_DaeGauntletTestActorBlueprint::FAssetTypeActions_DaeGauntletTestActorBlueprint(
    EAssetTypeCategories::Type InAssetTypeCategory)
    : AssetTypeCategory(InAssetTypeCategory)
{
}

FText FAssetTypeActions_DaeGauntletTestActorBlueprint::GetName() const
{
    return NSLOCTEXT("DaedalicTestAutomationPlugin",
                     "AssetTypeActions_DaeGauntletTestActorBlueprint", "Test Actor Blueprint");
}

UClass* FAssetTypeActions_DaeGauntletTestActorBlueprint::GetSupportedClass() const
{
    return UDaeGauntletTestActorBlueprint::StaticClass();
}

uint32 FAssetTypeActions_DaeGauntletTestActorBlueprint::GetCategories()
{
    return AssetTypeCategory;
}

UFactory* FAssetTypeActions_DaeGauntletTestActorBlueprint::GetFactoryForBlueprintType(
    UBlueprint* InBlueprint) const
{
    return NewObject<UDaeGauntletTestActorBlueprintFactory>();
}

#undef LOCTEXT_NAMESPACE
