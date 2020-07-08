#include "DaeTestReportWriter.h"

int32 FDaeTestReportWriter::NumTotalTests(const TArray<FDaeTestSuiteResult>& TestSuites) const
{
    int32 TotalTests = 0;

    for (const FDaeTestSuiteResult& TestSuite : TestSuites)
    {
        TotalTests += TestSuite.NumTotalTests();
    }

    return TotalTests;
}

int32 FDaeTestReportWriter::NumFailedTests(const TArray<FDaeTestSuiteResult>& TestSuites) const
{
    int32 FailedTests = 0;

    for (const FDaeTestSuiteResult& TestSuite : TestSuites)
    {
        FailedTests += TestSuite.NumFailedTests();
    }

    return FailedTests;
}

int32 FDaeTestReportWriter::NumSkippedTests(const TArray<FDaeTestSuiteResult>& TestSuites) const
{
    int32 SkippedTests = 0;

    for (const FDaeTestSuiteResult& TestSuite : TestSuites)
    {
        SkippedTests += TestSuite.NumSkippedTests();
    }

    return SkippedTests;
}

float FDaeTestReportWriter::GetTotalTimeSeconds(const TArray<FDaeTestSuiteResult>& TestSuites) const
{
    float TimeSeconds = 0;

    for (const FDaeTestSuiteResult& TestSuite : TestSuites)
    {
        TimeSeconds += TestSuite.GetTotalTimeSeconds();
    }

    return TimeSeconds;
}

FString FDaeTestReportWriter::GetTimestamp(const TArray<FDaeTestSuiteResult>& TestSuites) const
{
    FDateTime Timestamp = TestSuites.Num() > 0 ? TestSuites[0].Timestamp : FDateTime::UtcNow();
    return Timestamp.ToIso8601();
}

FString FDaeTestReportWriter::ApplyTemplateFile(const FString& TemplateFilePath,
                                                const TMap<FString, FString>& Replacements) const
{
    FString ResultString;
    FFileHelper::LoadFileToString(ResultString, *TemplateFilePath);

    for (auto& Replacement : Replacements)
    {
        ResultString = ResultString.Replace(*Replacement.Key, *Replacement.Value);
    }

    return ResultString;
}
