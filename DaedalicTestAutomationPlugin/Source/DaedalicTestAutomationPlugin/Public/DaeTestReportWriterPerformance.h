#pragma once

#include "DaeTestReportWriter.h"
#include "DaeTestSuiteResult.h"
#include <CoreMinimal.h>

/** Writes test reports for performance budgets. */
class DAEDALICTESTAUTOMATIONPLUGIN_API FDaeTestReportWriterPerformance : public FDaeTestReportWriter
{
public:
    virtual FName GetReportType() const override;
    virtual void WriteReport(const TArray<FDaeTestSuiteResult>& TestSuites,
                             const FString& ReportPath) const override;

private:
    /** Formats the specified time using a fixed number of fractional digits. */
    FString FormatTime(float Time) const;

    /** Formats the specified location using a fixed number of fractional digits. */
    FString FormatLocation(const FVector& Location) const;
};
