#pragma once

#include "DaeTestResult.h"

/** Result set of a whole test suite. */
class DAEDALICTESTAUTOMATIONPLUGIN_API FDaeTestSuiteResult
{
public:
    /** Name of the map the test suite ran in. */
    FString MapName;

    /** Name of the test suite that ran. */
    FString TestSuiteName;

    /** UTC date and time the test suite started running. */
    FDateTime Timestamp;

    /** Results of all individual tests of the test suite. */
    TArray<FDaeTestResult> TestResults;

    /** How many tests of the test suite have been run. */
    int32 NumTotalTests() const;

    /** How many tests of the test suite have been successful. */
    int32 NumSuccessfulTests() const;

    /** How many tests of the test suite have failed. */
    int32 NumFailedTests() const;

    /** Combined time all tests ran, in seconds. */
    float GetTotalTimeSeconds() const;
};
