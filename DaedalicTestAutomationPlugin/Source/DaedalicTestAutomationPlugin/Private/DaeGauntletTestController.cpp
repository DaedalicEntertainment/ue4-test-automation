#include "DaeGauntletTestController.h"
#include "DaeTestLogCategory.h"
#include "DaeTestSuiteActor.h"
#include <EngineUtils.h>

void UDaeGauntletTestController::OnPostMapChange(UWorld* World)
{
    UE_LOG(LogDaeTest, Log, TEXT("UDaeGauntletTestController::OnPostMapChange - World: %s"),
           *World->GetName());

    // Find test suite.
    ADaeTestSuiteActor* TestSuite = nullptr;

    for (TActorIterator<ADaeTestSuiteActor> ActorIt(World); ActorIt; ++ActorIt)
    {
        TestSuite = *ActorIt;
    }

    if (!IsValid(TestSuite))
    {
        UE_LOG(LogDaeTest, Error,
               TEXT("UDaeGauntletTestController::OnPostMapChange - No DaeGauntletTestSuiteActor "
                    "found."));
        EndTest(1);
    }

    // Start first test.
    TestSuite->OnTestSuiteSuccessful.AddDynamic(this,
                                                &UDaeGauntletTestController::OnTestSuiteSuccessful);
    TestSuite->OnTestSuiteFailed.AddDynamic(this, &UDaeGauntletTestController::OnTestSuiteFailed);

    TestSuite->RunAllTests();
}

void UDaeGauntletTestController::OnTestSuiteSuccessful(ADaeTestSuiteActor* TestSuite)
{
    EndTest(0);
}

void UDaeGauntletTestController::OnTestSuiteFailed(ADaeTestSuiteActor* TestSuite)
{
    EndTest(1);
}
