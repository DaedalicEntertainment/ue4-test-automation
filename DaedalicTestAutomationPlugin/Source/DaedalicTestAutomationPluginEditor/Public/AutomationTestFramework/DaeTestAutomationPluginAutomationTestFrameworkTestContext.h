#pragma once

#include <CoreMinimal.h>

class ADaeGauntletTestSuiteActor;

/** Context to run a single test for the Unreal Automation Test Framework within. */
class FDaeTestAutomationPluginAutomationTestFrameworkTestContext
{
public:
    ADaeGauntletTestSuiteActor* CurrentTestSuite;

    FDaeTestAutomationPluginAutomationTestFrameworkTestContext();
};
