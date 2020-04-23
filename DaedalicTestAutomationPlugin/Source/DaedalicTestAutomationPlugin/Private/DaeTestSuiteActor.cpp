#include "DaeTestSuiteActor.h"
#include "DaeTestLogCategory.h"

ADaeTestSuiteActor::ADaeTestSuiteActor(
    const FObjectInitializer& ObjectInitializer /*= FObjectInitializer::Get()*/)
{
    bRunInPIE = true;
    TestIndex = -1;
}

void ADaeTestSuiteActor::BeginPlay()
{
    Super::BeginPlay();

    if (bRunInPIE && GetWorld()->IsPlayInEditor())
    {
        RunAllTests();
    }
}

void ADaeTestSuiteActor::RunAllTests()
{
    UE_LOG(LogDaeTest, Log, TEXT("ADaeTestSuiteActor::RunAllTests - Test Suite: %s"), *GetName());

    TestIndex = -1;
    RunNextTest();
}

bool ADaeTestSuiteActor::IsRunning() const
{
    return Tests.IsValidIndex(TestIndex);
}

void ADaeTestSuiteActor::RunNextTest()
{
    // Unregister events.
    if (Tests.IsValidIndex(TestIndex))
    {
        ADaeTestActor* Test = Tests[TestIndex];

        Test->OnTestSuccessful.RemoveDynamic(this, &ADaeTestSuiteActor::OnTestSuccessful);
        Test->OnTestFailed.RemoveDynamic(this, &ADaeTestSuiteActor::OnTestFailed);
    }

    // Prepare next test.
    ++TestIndex;

    if (!Tests.IsValidIndex(TestIndex))
    {
        // All tests finished.
        UE_LOG(LogDaeTest, Log, TEXT("ADaeTestSuiteActor::RunNextTest - All tests finished."));

        OnTestSuiteSuccessful.Broadcast(this);
        return;
    }

    ADaeTestActor* Test = Tests[TestIndex];

    UE_LOG(LogDaeTest, Log, TEXT("ADaeTestSuiteActor::RunNextTest - Test: %s"), *Test->GetName());

    // Register events.
    Test->OnTestSuccessful.AddDynamic(this, &ADaeTestSuiteActor::OnTestSuccessful);
    Test->OnTestFailed.AddDynamic(this, &ADaeTestSuiteActor::OnTestFailed);

    // Run test.
    Test->RunTest();
}

void ADaeTestSuiteActor::OnTestSuccessful(ADaeTestActor* Test)
{
    UE_LOG(LogDaeTest, Log, TEXT("ADaeTestSuiteActor::TestSuccessful - Test: %s"),
           *Test->GetName());

    RunNextTest();
}

void ADaeTestSuiteActor::OnTestFailed(ADaeTestActor* Test)
{
    UE_LOG(LogDaeTest, Error, TEXT("ADaeTestSuiteActor::TestFailed - Test: %s"), *Test->GetName());

    TestIndex = -1;

    OnTestSuiteFailed.Broadcast(this);
}
