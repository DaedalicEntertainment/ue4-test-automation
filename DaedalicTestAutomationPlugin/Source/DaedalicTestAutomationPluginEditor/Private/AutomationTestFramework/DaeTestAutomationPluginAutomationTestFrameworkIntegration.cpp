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

    UE_LOG(LogDaeTestEditor, Log, TEXT("Discovering tests from: %s"),
           *TestAutomationPluginSettings->TestMapPath);

    // Unregister existing tests.
    Tests.Empty();

    // Register new tests (based on FLoadAllMapsInEditorTest).
    TArray<FString> PackageFiles;
    FEditorFileUtils::FindAllPackageFiles(PackageFiles);

    // Iterate over all files, adding the ones with the map extension.
    const FString PatternToCheck =
        FString::Printf(TEXT("/%s/"), *TestAutomationPluginSettings->TestMapPath);

    for (const FString& Filename : PackageFiles)
    {
        bool bIsMap = FPaths::GetExtension(Filename, true)
                      == FPackageName::GetMapPackageExtension();
        FName AssetName = FName(*FPaths::GetBaseFilename(Filename));

        if (bIsMap
            && (Filename.Contains(*PatternToCheck)
                || TestAutomationPluginSettings->AdditionalTestMaps.Contains(AssetName)))
        {
            TSharedPtr<FDaeTestAutomationPluginAutomationTestFrameworkTest> NewTest =
                MakeShareable(new FDaeTestAutomationPluginAutomationTestFrameworkTest(Filename));
            Tests.Add(NewTest);

            UE_LOG(LogDaeTestEditor, Log, TEXT("Discovered test: %s"), *NewTest->GetMapName());
        }
    }
}
