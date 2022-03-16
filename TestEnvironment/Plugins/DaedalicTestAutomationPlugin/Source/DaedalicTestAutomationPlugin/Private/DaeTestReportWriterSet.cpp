#include "DaeTestReportWriterSet.h"
#include "DaeTestReportWriter.h"

void FDaeTestReportWriterSet::Add(TSharedPtr<FDaeTestReportWriter> ReportWriter)
{
    for (TSharedPtr<FDaeTestReportWriter> ExistingReportWriter : ReportWriters)
    {
        if (ExistingReportWriter->GetReportType() == ReportWriter->GetReportType())
        {
            return;
        }
    }

    ReportWriters.Add(ReportWriter);
}

void FDaeTestReportWriterSet::Add(const FDaeTestReportWriterSet& Other)
{
    for (TSharedPtr<FDaeTestReportWriter> ReportWriter : Other.GetReportWriters())
    {
        Add(ReportWriter);
    }
}

TArray<TSharedPtr<FDaeTestReportWriter>> FDaeTestReportWriterSet::GetReportWriters() const
{
    return ReportWriters;
}
