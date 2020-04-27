#include "DaeTestSuiteResult.h"

int32 FDaeTestSuiteResult::NumTotalTests() const
{
    return TestResults.Num();
}

int32 FDaeTestSuiteResult::NumSuccessfulTests() const
{
    int32 SuccessfulTests = 0;

    for (const FDaeTestResult& TestResult : TestResults)
    {
        if (TestResult.IsSuccessful())
        {
            ++SuccessfulTests;
        }
    }

    return SuccessfulTests;
}

int32 FDaeTestSuiteResult::NumFailedTests() const
{
    return NumTotalTests() - NumSuccessfulTests();
}

float FDaeTestSuiteResult::GetTotalTimeSeconds() const
{
    float TimeSeconds = 0.0f;

    for (const FDaeTestResult& TestResult : TestResults)
    {
        TimeSeconds += TestResult.TimeSeconds;
    }

    return TimeSeconds;
}
