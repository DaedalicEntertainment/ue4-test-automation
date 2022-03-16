#include "DaeTestAutomationPluginSettings.h"
#include "DaeTestLogCategory.h"

UDaeTestAutomationPluginSettings::UDaeTestAutomationPluginSettings()
{
}

void UDaeTestAutomationPluginSettings::PostInitProperties()
{
    Super::PostInitProperties();

    // Backwards compatibility.
    if (!TestMapPath.IsEmpty())
    {
        TestMapFolders.AddUnique(TestMapPath);
        TestMapPath = TEXT("");

        UE_LOG(LogDaeTest, Warning,
               TEXT("Found deprecated configuration value TestMapPath in Daedalic Test Automation "
                    "Plugin settings. We have automatically upgraded your settings to use "
                    "TestMapFolders instead. Please review and save your changes before upgrading "
                    "to future versions of the plugin."));
    }
}

#if WITH_EDITOR
void UDaeTestAutomationPluginSettings::PostEditChangeProperty(
    struct FPropertyChangedEvent& PropertyChangedEvent)
{
    if (PropertyChangedEvent.GetPropertyName() == TEXT("TestMapFolders")
        || PropertyChangedEvent.GetPropertyName() == TEXT("AdditionalTestMaps")
        || PropertyChangedEvent.GetPropertyName() == TEXT("IgnoredMaps"))
    {
        OnTestMapsChanged.Broadcast();
        return;
    }
}
#endif

bool UDaeTestAutomationPluginSettings::IsTestMap(const FString& FileName,
                                                 const FName& MapName) const
{
    bool bIsTestMap = false;

    for (const FString& TestMapFolder : TestMapFolders)
    {
        const FString PatternToCheck = FString::Printf(TEXT("/%s/"), *TestMapFolder);
        bIsTestMap = bIsTestMap || FileName.Contains(*PatternToCheck);
    }

    bIsTestMap = bIsTestMap || AdditionalTestMaps.Contains(MapName);
    bIsTestMap = bIsTestMap && !IgnoredMaps.Contains(MapName);

    return bIsTestMap;
}
