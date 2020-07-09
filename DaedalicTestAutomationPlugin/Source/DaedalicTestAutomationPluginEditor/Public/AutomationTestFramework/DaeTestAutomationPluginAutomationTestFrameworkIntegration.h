#pragma once

#include "DaeTestAutomationPluginAutomationTestFrameworkTest.h"
#include <CoreMinimal.h>

/** Integration with the Unreal Automation Test Framework. Discovers tests based on the plugin settings. */
class FDaeTestAutomationPluginAutomationTestFrameworkIntegration
{
public:
    /** Discovers all maps containing automated tests. */
    void DiscoverTests();

private:
    /** Currently registered automation tests. */
    TArray<TSharedPtr<FDaeTestAutomationPluginAutomationTestFrameworkTest>> Tests;
};
