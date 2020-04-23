#include "DaeTestAutomationPluginEditorSettings.h"
#include "DaeTestEditorLogCategory.h"

UDaeTestAutomationPluginEditorSettings::UDaeTestAutomationPluginEditorSettings()
    : TestMapPath(TEXT("Maps/AutomatedTests"))
{
}

void UDaeTestAutomationPluginEditorSettings::PostEditChangeProperty(
    struct FPropertyChangedEvent& PropertyChangedEvent)
{
    if (PropertyChangedEvent.GetPropertyName() == TEXT("TestMapPath"))
    {
        OnTestMapPathChanged.Broadcast(TestMapPath);
    }
}
