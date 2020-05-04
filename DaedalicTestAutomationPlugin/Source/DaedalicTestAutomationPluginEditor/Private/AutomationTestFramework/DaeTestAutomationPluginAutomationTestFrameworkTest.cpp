#include "DaeTestAutomationPluginAutomationTestFrameworkTest.h"
#include "DaeTestAutomationPluginAutomationTestFrameworkCommands.h"
#include "DaeTestAutomationPluginAutomationTestFrameworkTestContext.h"
#include "DaeTestEditorLogCategory.h"
#include <AutomationCommon.h>
#include <AutomationEditorCommon.h>
#include <Misc/Paths.h>

FDaeTestAutomationPluginAutomationTestFrameworkTest::
    FDaeTestAutomationPluginAutomationTestFrameworkTest(const FString& InMapName)
    : FAutomationTestBase(InMapName, false)
    , MapName(InMapName)
{
    // Test is automatically registered in FAutomationTestBase base class constructor.
}

uint32 FDaeTestAutomationPluginAutomationTestFrameworkTest::GetTestFlags() const
{
    return EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter;
}

uint32 FDaeTestAutomationPluginAutomationTestFrameworkTest::GetRequiredDeviceNum() const
{
    return 1;
}

FString FDaeTestAutomationPluginAutomationTestFrameworkTest::GetTestSourceFileName() const
{
    return GetMapName();
}

int32 FDaeTestAutomationPluginAutomationTestFrameworkTest::GetTestSourceFileLine() const
{
    return 0;
}

FString FDaeTestAutomationPluginAutomationTestFrameworkTest::GetMapName() const
{
    return MapName;
}

void FDaeTestAutomationPluginAutomationTestFrameworkTest::GetTests(
    TArray<FString>& OutBeautifiedNames, TArray<FString>& OutTestCommands) const
{
    OutBeautifiedNames.Add(GetBeautifiedTestName());
    OutTestCommands.Add(FString());
}

bool FDaeTestAutomationPluginAutomationTestFrameworkTest::RunTest(const FString& Parameters)
{
    UE_LOG(LogDaeTestEditor, Log, TEXT("Running test for map: %s"), *MapName);

    FDaeTestAutomationPluginAutomationTestFrameworkTestContext Context;

    ADD_LATENT_AUTOMATION_COMMAND(FEditorLoadMap(MapName));
    ADD_LATENT_AUTOMATION_COMMAND(FStartPIECommand(false));
    ADD_LATENT_AUTOMATION_COMMAND(FDaeTestAutomationPluginWaitForEndOfTestSuite(Context));
    ADD_LATENT_AUTOMATION_COMMAND(FEndPlayMapCommand());

    return true;
}

FString FDaeTestAutomationPluginAutomationTestFrameworkTest::GetBeautifiedTestName() const
{
    return TEXT("DaedalicTestAutomationPlugin.") + FPaths::GetBaseFilename(MapName);
}
