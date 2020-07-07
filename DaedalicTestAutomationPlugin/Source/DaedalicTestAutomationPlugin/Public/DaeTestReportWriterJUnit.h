#pragma once

#include "DaeTestReportWriter.h"
#include "DaeTestSuiteResult.h"
#include <CoreMinimal.h>

/** Writes test reports based on the Apache Ant JUnit report format (based on org.junit.platform.reporting.legacy.xml.XmlReportWriter.writeTestsuite). */
class DAEDALICTESTAUTOMATIONPLUGIN_API FDaeTestReportWriterJUnit : public FDaeTestReportWriter
{
public:
    virtual FName GetReportType() const override;
    virtual void WriteReport(const TArray<FDaeTestSuiteResult>& TestSuites,
                             const FString& ReportPath) const override;
};
