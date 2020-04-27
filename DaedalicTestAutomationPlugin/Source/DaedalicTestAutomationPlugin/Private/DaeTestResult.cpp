#include "DaeTestResult.h"

FDaeTestResult::FDaeTestResult()
    : FDaeTestResult(FString(), 0.0f)
{
}

FDaeTestResult::FDaeTestResult(FString InTestName, float InTimeSeconds)
    : TestName(InTestName)
    , TimeSeconds(InTimeSeconds)
{
}

bool FDaeTestResult::IsSuccessful() const
{
    return FailureMessage.IsEmpty();
}
