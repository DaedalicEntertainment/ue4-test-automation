#include "AutomationTestFramework/DaeTestAutomationPluginAutomationTestFrameworkIntegration.h"
#include "DaeTestAutomationPluginSettings.h"
#include "DaeTestEditorLogCategory.h"
#include <FileHelpers.h>
#include <Misc/PackageName.h>
#include <Misc/Paths.h>

void FDaeTestAutomationPluginAutomationTestFrameworkIntegration::DiscoverTests()
{
    const UDaeTestAutomationPluginSettings* TestAutomationPluginSettings =
        GetDefault<UDaeTestAutomationPluginSettings>();

    for (const FString& TestMapFolder : TestAutomationPluginSettings->TestMapFolders)
    {
        UE_LOG(LogDaeTestEditor, Log, TEXT("Discovering tests from: %s"), *TestMapFolder);
    }

    // Unregister existing tests.
    Tests.Empty();

    // Register new tests (based on FLoadAllMapsInEditorTest).
    TArray<FString> PackageFiles;
    FEditorFileUtils::FindAllPackageFiles(PackageFiles);

    // Iterate over all files, adding the ones with the map extension.
    for (const FString& FileName : PackageFiles)
    {
        bool bIsMap = FPaths::GetExtension(FileName, true)
                      == FPackageName::GetMapPackageExtension();
        FName MapName = FName(*FPaths::GetBaseFilename(FileName));

        if (bIsMap && TestAutomationPluginSettings->IsTestMap(FileName, MapName))
        {
            TSharedPtr<FDaeTestAutomationPluginAutomationTestFrameworkTest> NewTest =
                MakeShareable(new FDaeTestAutomationPluginAutomationTestFrameworkTest(FileName));
            Tests.Add(NewTest);

            UE_LOG(LogDaeTestEditor, Log, TEXT("Discovered test: %s"), *NewTest->GetMapName());
        }
    }
}
