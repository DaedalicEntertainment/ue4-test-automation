#include "AutomationTestFramework/DaeTestAutomationPluginAutomationTestFrameworkCommands.h"
#include "DaeTestAutomationPluginSettings.h"
#include "DaeTestEditorLogCategory.h"
#include "DaeTestSuiteActor.h"
#include <Editor.h>
#include <EngineUtils.h>
#include <Editor/UnrealEdEngine.h>

bool FDaeTestAutomationPluginWaitForEndOfTestSuite::Update()
{
    if (!GEditor)
    {
        return false;
    }

    if (!GEditor->PlayWorld)
    {
        return false;
    }

    if (!Context.CurrentTestSuite)
    {
        for (TActorIterator<ADaeTestSuiteActor> Iter(GEditor->PlayWorld); Iter; ++Iter)
        {
            Context.CurrentTestSuite = *Iter;
        }
    }

    if (Context.CurrentTestSuite)
    {
        return !Context.CurrentTestSuite->IsRunning();
    }

    return false;
}

bool FDaeTestAutomationPluginApplyConsoleVariables::Update()
{
    Context.OldConsoleVariables.Empty();

    const UDaeTestAutomationPluginSettings* Settings =
        GetDefault<UDaeTestAutomationPluginSettings>();

    for (auto& ConsoleVariable : Settings->ConsoleVariables)
    {
        IConsoleVariable* CVar = IConsoleManager::Get().FindConsoleVariable(*ConsoleVariable.Key);

        if (CVar)
        {
            FString OldValue = CVar->GetString();
            CVar->Set(*ConsoleVariable.Value);

            Context.OldConsoleVariables.Add(ConsoleVariable.Key, OldValue);

            UE_LOG(LogDaeTestEditor, Log, TEXT("Setting console variable %s = %s"),
                   *ConsoleVariable.Key, *ConsoleVariable.Value);
        }
    }

    return true;
}

bool FDaeTestAutomationPluginRevertConsoleVariables::Update()
{
    for (auto& ConsoleVariable : Context.OldConsoleVariables)
    {
        IConsoleVariable* CVar = IConsoleManager::Get().FindConsoleVariable(*ConsoleVariable.Key);

        if (CVar)
        {
            CVar->Set(*ConsoleVariable.Value);

            UE_LOG(LogDaeTestEditor, Log, TEXT("Restoring console variable %s = %s"),
                   *ConsoleVariable.Key, *ConsoleVariable.Value);
        }
    }

    return true;
}
