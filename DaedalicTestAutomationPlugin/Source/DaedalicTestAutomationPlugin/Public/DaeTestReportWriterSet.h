#pragma once

#include <CoreMinimal.h>

class FDaeTestReportWriter;

/** Writes multiple different test reports, e.g. for publishing with CI/CD pipelines. */
class DAEDALICTESTAUTOMATIONPLUGIN_API FDaeTestReportWriterSet
{
public:
    /** Adds the specified report writer to this set. */
    void Add(TSharedPtr<FDaeTestReportWriter> ReportWriter);

    /** Adds the specified report writers to this set. */
    void Add(const FDaeTestReportWriterSet& Other);

    /** Gets the report writers of this set. */
    TArray<TSharedPtr<FDaeTestReportWriter>> GetReportWriters() const;

private:
    TArray<TSharedPtr<FDaeTestReportWriter>> ReportWriters;
};
