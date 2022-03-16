#pragma once

#include "DaeTestAutomationPluginAutomationTestFrameworkTestContext.h"
#include <CoreMinimal.h>
#include <Misc/AutomationTest.h>

class ADaeTestSuiteActor;

/** Waits for the current test suite to finish. */
DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(
    FDaeTestAutomationPluginWaitForEndOfTestSuite,
    FDaeTestAutomationPluginAutomationTestFrameworkTestContext&, Context);

/** Applies console variables for the test. */
DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(
    FDaeTestAutomationPluginApplyConsoleVariables,
    FDaeTestAutomationPluginAutomationTestFrameworkTestContext&, Context);

/** Restores console variables after the test. */
DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(
    FDaeTestAutomationPluginRevertConsoleVariables,
    FDaeTestAutomationPluginAutomationTestFrameworkTestContext&, Context);
