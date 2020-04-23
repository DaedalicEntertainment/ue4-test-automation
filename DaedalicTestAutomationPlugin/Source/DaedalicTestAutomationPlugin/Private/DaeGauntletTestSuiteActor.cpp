#include "DaeGauntletTestSuiteActor.h"
#include "DaeTestLogCategory.h"

ADaeGauntletTestSuiteActor::ADaeGauntletTestSuiteActor(
    const FObjectInitializer& ObjectInitializer /*= FObjectInitializer::Get()*/)
{
    bRunInPIE = true;
    TestIndex = -1;
}

void ADaeGauntletTestSuiteActor::BeginPlay()
{
    Super::BeginPlay();

    if (bRunInPIE && GetWorld()->IsPlayInEditor())
    {
        RunAllTests();
    }
}

void ADaeGauntletTestSuiteActor::RunAllTests()
{
    UE_LOG(LogDaeTest, Log, TEXT("ADaeGauntletTestSuiteActor::RunAllTests - Test Suite: %s"),
           *GetName());

    TestIndex = -1;
    RunNextTest();
}

bool ADaeGauntletTestSuiteActor::IsRunning() const
{
    return Tests.IsValidIndex(TestIndex);
}

void ADaeGauntletTestSuiteActor::RunNextTest()
{
    // Unregister events.
    if (Tests.IsValidIndex(TestIndex))
    {
        ADaeGauntletTestActor* Test = Tests[TestIndex];

        Test->OnTestSuccessful.RemoveDynamic(this, &ADaeGauntletTestSuiteActor::OnTestSuccessful);
        Test->OnTestFailed.RemoveDynamic(this, &ADaeGauntletTestSuiteActor::OnTestFailed);
    }

    // Prepare next test.
    ++TestIndex;

    if (!Tests.IsValidIndex(TestIndex))
    {
        // All tests finished.
        UE_LOG(LogDaeTest, Log,
               TEXT("ADaeGauntletTestSuiteActor::RunNextTest - All tests finished."));

        OnTestSuiteSuccessful.Broadcast(this);
        return;
    }

    ADaeGauntletTestActor* Test = Tests[TestIndex];

    UE_LOG(LogDaeTest, Log, TEXT("ADaeGauntletTestSuiteActor::RunNextTest - Test: %s"),
           *Test->GetName());

    // Register events.
    Test->OnTestSuccessful.AddDynamic(this, &ADaeGauntletTestSuiteActor::OnTestSuccessful);
    Test->OnTestFailed.AddDynamic(this, &ADaeGauntletTestSuiteActor::OnTestFailed);

    // Run test.
    Test->RunTest();
}

void ADaeGauntletTestSuiteActor::OnTestSuccessful(ADaeGauntletTestActor* Test)
{
    UE_LOG(LogDaeTest, Log, TEXT("ADaeGauntletTestSuiteActor::TestSuccessful - Test: %s"),
           *Test->GetName());

    RunNextTest();
}

void ADaeGauntletTestSuiteActor::OnTestFailed(ADaeGauntletTestActor* Test)
{
    UE_LOG(LogDaeTest, Error, TEXT("ADaeGauntletTestSuiteActor::TestFailed - Test: %s"),
           *Test->GetName());

    TestIndex = -1;

    OnTestSuiteFailed.Broadcast(this);
}
