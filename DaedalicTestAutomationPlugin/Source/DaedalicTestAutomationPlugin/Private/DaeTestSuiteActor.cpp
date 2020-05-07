#include "DaeTestSuiteActor.h"
#include "DaeTestActor.h"
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
}

void ADaeTestSuiteActor::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    if (!IsRunning())
    {
        // Check if we should run all tests immediately.
        // Happening in first Tick to make sure all actors have begun play.
        if (bRunInPIE && GetWorld()->IsPlayInEditor() && TestIndex < 0)
        {
            RunAllTests();
        }

        return;
    }

    TestTimeSeconds += DeltaSeconds;

    ADaeTestActor* CurrentTest = GetCurrentTest();

    if (TestTimeSeconds >= CurrentTest->GetTimeoutInSeconds())
    {
        // Enough waiting. Let's see the results.
        UE_LOG(LogDaeTest, Warning, TEXT("Timed out after %f seconds"),
               CurrentTest->GetTimeoutInSeconds());

        CurrentTest->FinishAct();
    }
}

void ADaeTestSuiteActor::RunAllTests()
{
    UE_LOG(LogDaeTest, Display, TEXT("ADaeTestSuiteActor::RunAllTests - Test Suite: %s"),
           *GetName());

    NotifyOnBeforeAll();
    TestIndex = -1;
    RunNextTest();
}

bool ADaeTestSuiteActor::IsRunning() const
{
    return IsValid(GetCurrentTest());
}

ADaeTestActor* ADaeTestSuiteActor::GetCurrentTest() const
{
    return Tests.IsValidIndex(TestIndex) ? Tests[TestIndex] : nullptr;
}

FDaeTestSuiteResult ADaeTestSuiteActor::GetResult() const
{
    return Result;
}

void ADaeTestSuiteActor::NotifyOnBeforeAll()
{
    ReceiveOnBeforeAll();
}

void ADaeTestSuiteActor::NotifyOnAfterAll()
{
    ReceiveOnAfterAll();
}

void ADaeTestSuiteActor::NotifyOnBeforeEach()
{
    ReceiveOnBeforeEach();
}

void ADaeTestSuiteActor::NotifyOnAfterEach()
{
    ReceiveOnAfterEach();
}

void ADaeTestSuiteActor::RunNextTest()
{
    ADaeTestActor* CurrentTest = GetCurrentTest();

    // Unregister events.
    if (IsValid(CurrentTest))
    {
        CurrentTest->OnTestSuccessful.RemoveDynamic(this, &ADaeTestSuiteActor::OnTestSuccessful);
        CurrentTest->OnTestFailed.RemoveDynamic(this, &ADaeTestSuiteActor::OnTestFailed);
        CurrentTest->OnTestSkipped.RemoveDynamic(this, &ADaeTestSuiteActor::OnTestSkipped);
    }

    // Prepare next test.
    ++TestIndex;
    TestTimeSeconds = 0.0f;

    if (!Tests.IsValidIndex(TestIndex))
    {
        // All tests finished.
        UE_LOG(LogDaeTest, Display, TEXT("ADaeTestSuiteActor::RunNextTest - All tests finished."));

        NotifyOnAfterAll();

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

    if (IsValid(Test))
    {
        UE_LOG(LogDaeTest, Display, TEXT("ADaeTestSuiteActor::RunNextTest - Test: %s"),
               *Test->GetName());

        // Register events.
        Test->OnTestSuccessful.AddDynamic(this, &ADaeTestSuiteActor::OnTestSuccessful);
        Test->OnTestFailed.AddDynamic(this, &ADaeTestSuiteActor::OnTestFailed);
        Test->OnTestSkipped.AddDynamic(this, &ADaeTestSuiteActor::OnTestSkipped);

        // Run test.
        NotifyOnBeforeEach();

        Test->RunTest();
    }
    else
    {
        UE_LOG(LogDaeTest, Error,
               TEXT("ADaeTestSuiteActor::RunNextTest - %s has invalid test at index %i, skipping."),
               *GetName(), TestIndex);

        RunNextTest();
    }
}

void ADaeTestSuiteActor::OnTestSuccessful(ADaeTestActor* Test)
{
    if (Test != GetCurrentTest())
    {
        // Prevent tests from reporting multiple results.
        return;
    }

    UE_LOG(LogDaeTest, Display, TEXT("ADaeTestSuiteActor::OnTestSuccessful - Test: %s"),
           *Test->GetName());

    // Store result.
    FDaeTestResult TestResult(Test->GetName(), TestTimeSeconds);
    Result.TestResults.Add(TestResult);

    // Run next test.
    NotifyOnAfterEach();

    RunNextTest();
}

void ADaeTestSuiteActor::OnTestFailed(ADaeTestActor* Test, const FString& FailureMessage)
{
    if (Test != GetCurrentTest())
    {
        // Prevent tests from reporting multiple results.
        return;
    }

    UE_LOG(LogDaeTest, Error,
           TEXT("ADaeTestSuiteActor::OnTestFailed - Test: %s, FailureMessage: %s"),
           *Test->GetName(), *FailureMessage);

    // Store result.
    FDaeTestResult TestResult(Test->GetName(), TestTimeSeconds);
    TestResult.FailureMessage = FailureMessage;
    Result.TestResults.Add(TestResult);

    // Run next test.
    NotifyOnAfterEach();

    RunNextTest();
}

void ADaeTestSuiteActor::OnTestSkipped(ADaeTestActor* Test, const FString& SkipReason)
{
    if (Test != GetCurrentTest())
    {
        // Prevent tests from reporting multiple results.
        return;
    }

    UE_LOG(LogDaeTest, Display,
           TEXT("ADaeTestSuiteActor::OnTestSkipped - Test: %s, SkipReason: %s"), *Test->GetName(),
           *SkipReason);

    // Store result.
    FDaeTestResult TestResult(Test->GetName(), TestTimeSeconds);
    TestResult.SkipReason = SkipReason;
    Result.TestResults.Add(TestResult);

    // Run next test.
    RunNextTest();
}
