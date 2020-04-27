#pragma once

/** Result set of a single test. */
class DAEDALICTESTAUTOMATIONPLUGIN_API FDaeTestResult
{
public:
    /** Name of the test. */
    FString TestName;

    /** (Optional) Why the test failed. */
    FString FailureMessage;

    /** Time the test ran, in seconds. */
    float TimeSeconds;

    FDaeTestResult();
    FDaeTestResult(FString InTestName, float InTimeSeconds);

    /** Whether the test finished without failure, or not. */
    bool IsSuccessful() const;
};
