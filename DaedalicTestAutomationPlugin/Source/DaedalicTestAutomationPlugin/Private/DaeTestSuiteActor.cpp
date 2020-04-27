#include "DaeTestSuiteActor.h"
#include "DaeTestLogCategory.h"

ADaeTestSuiteActor::ADaeTestSuiteActor(
    const FObjectInitializer& ObjectInitializer /*= FObjectInitializer::Get()*/)
{
    bRunInPIE = true;
    TestIndex = -1;

    PrimaryActorTick.bCanEverTick = true;
}

void ADaeTestSuiteActor::BeginPlay()
{
    Super::BeginPlay();

    // Setup result data.
    Result.MapName = GetWorld()->GetMapName();
    Result.TestSuiteName = GetName();
    Result.Timestamp = FDateTime::UtcNow();

    // Check if we should run all tests immediately.
    if (bRunInPIE && GetWorld()->IsPlayInEditor())
    {
        RunAllTests();
    }
}

void ADaeTestSuiteActor::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    TestTimeSeconds += DeltaSeconds;
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

FDaeTestSuiteResult ADaeTestSuiteActor::GetResult() const
{
    return Result;
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
    TestTimeSeconds = 0.0f;

    if (!Tests.IsValidIndex(TestIndex))
    {
        // All tests finished.
        UE_LOG(LogDaeTest, Log, TEXT("ADaeTestSuiteActor::RunNextTest - All tests finished."));

        // Check if any test failed.
        for (const FDaeTestResult& TestResult : Result.TestResults)
        {
            if (!TestResult.FailureMessage.IsEmpty())
            {
                OnTestSuiteFailed.Broadcast(this);
                return;
            }
        }

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

    // Store result.
    FDaeTestResult TestResult(Test->GetName(), TestTimeSeconds);
    Result.TestResults.Add(TestResult);

    // Run next test.
    RunNextTest();
}

void ADaeTestSuiteActor::OnTestFailed(ADaeTestActor* Test, const FString& FailureMessage)
{
    UE_LOG(LogDaeTest, Error, TEXT("ADaeTestSuiteActor::TestFailed - Test: %s, FailureMessage: %s"),
           *Test->GetName(), *FailureMessage);

    // Store result.
    FDaeTestResult TestResult(Test->GetName(), TestTimeSeconds);
    TestResult.FailureMessage = FailureMessage;
    Result.TestResults.Add(TestResult);

    // Run next test
    RunNextTest();
}
