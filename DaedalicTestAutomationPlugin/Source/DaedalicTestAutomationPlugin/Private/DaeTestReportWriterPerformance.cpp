#include "DaeTestReportWriterPerformance.h"
#include "DaeTestPerformanceBudgetResultData.h"
#include "DaeTestPerformanceBudgetViolation.h"
#include <HAL/PlatformFilemanager.h>
#include <Kismet/KismetTextLibrary.h>

FName FDaeTestReportWriterPerformance::GetReportType() const
{
    return TEXT("FDaeTestReportWriterPerformance");
}

void FDaeTestReportWriterPerformance::WriteReport(const TArray<FDaeTestSuiteResult>& TestSuites,
                                                  const FString& ReportPath) const
{
    // Build report path.
    FString HtmlReportPath = FPaths::Combine(ReportPath, TEXT("performance-report.html"));

    // Write report header.
    FString HtmlString;

    HtmlString += TEXT("<!doctype html>") LINE_TERMINATOR;
    HtmlString += TEXT("<html lang=\"en\">") LINE_TERMINATOR;
    HtmlString += TEXT("  <head>") LINE_TERMINATOR;
    HtmlString += TEXT("    <meta charset=\"utf-8\">") LINE_TERMINATOR;
    HtmlString += TEXT("    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1, "
                       "shrink-to-fit=no\">") LINE_TERMINATOR;
    HtmlString +=
        TEXT("    <link rel=\"stylesheet\" "
             "href=\"https://stackpath.bootstrapcdn.com/bootstrap/4.5.0/css/bootstrap.min.css\" "
             "integrity=\"sha384-9aIt2nRpC12Uk9gS9baDl411NQApFmC26EwAOH8WgZl5MYYxFfc+"
             "NcPb1dKGj7Sk\" crossorigin=\"anonymous\">") LINE_TERMINATOR;
    HtmlString += TEXT("    <title>Performance Report</title>") LINE_TERMINATOR;
    HtmlString += TEXT("  </head>") LINE_TERMINATOR;

    HtmlString += TEXT("  <body>") LINE_TERMINATOR;
    HtmlString += TEXT("    <div class=\"container\">") LINE_TERMINATOR;
    HtmlString += TEXT("      <h1>Performance Report</h1>") LINE_TERMINATOR;

    // Write start time.
    HtmlString += TEXT("      <div class=\"row\">") LINE_TERMINATOR;
    HtmlString += TEXT("        <div class=\"col-3\"><strong>Start Time:</strong></div>")
        LINE_TERMINATOR;
    HtmlString +=
        FString::Printf(TEXT("        <div class=\"col-3\">%s</div>"), *GetTimestamp(TestSuites))
        + LINE_TERMINATOR;
    HtmlString += TEXT("      </div>") LINE_TERMINATOR;

    // Write total time.
    HtmlString += TEXT("      <div class=\"row\">") LINE_TERMINATOR;
    HtmlString +=
        TEXT("        <div class=\"col-3\"><strong>Total Duration (Seconds):</strong></div>")
            LINE_TERMINATOR;
    HtmlString += FString::Printf(TEXT("        <div class=\"col-3\">%s</div>"),
                                  *FormatTime(GetTotalTimeSeconds(TestSuites)))
                  + LINE_TERMINATOR;
    HtmlString += TEXT("      </div>") LINE_TERMINATOR;
    HtmlString += TEXT("      <p></p>") LINE_TERMINATOR;

    // Write performance violations.
    for (const FDaeTestSuiteResult& TestSuiteResult : TestSuites)
    {
        bool bHeaderWritten = false;

        for (const FDaeTestResult& TestResult : TestSuiteResult.TestResults)
        {
            if (TestResult.Data != nullptr
                && TestResult.Data->GetDataType() == TEXT("FDaeTestPerformanceBudgetResultData"))
            {
                TSharedPtr<FDaeTestPerformanceBudgetResultData> Data =
                    StaticCastSharedPtr<FDaeTestPerformanceBudgetResultData>(TestResult.Data);

                // Write header.
                if (!bHeaderWritten)
                {
                    HtmlString +=
                        FString::Printf(TEXT("      <h2>%s</h2>"), *TestSuiteResult.MapName)
                        + LINE_TERMINATOR;

                    bHeaderWritten = true;
                }

                // Write time.
                HtmlString += TEXT("      <div class=\"row\">") LINE_TERMINATOR;
                HtmlString +=
                    TEXT("        <div class=\"col-3\"><strong>Duration (Seconds):</strong></div>")
                        LINE_TERMINATOR;
                HtmlString += FString::Printf(TEXT("        <div class=\"col-3\">%s</div>"),
                                              *FormatTime(TestResult.TimeSeconds))
                              + LINE_TERMINATOR;
                HtmlString += TEXT("      </div>") LINE_TERMINATOR;
                HtmlString += TEXT("      <p></p>") LINE_TERMINATOR;

                // Write table header.
                HtmlString += TEXT("      <table class=\"table table-striped\">") LINE_TERMINATOR;
                HtmlString += TEXT("        <thead>") LINE_TERMINATOR;
                HtmlString += TEXT("          <tr>") LINE_TERMINATOR;
                HtmlString += TEXT("            <th scope=\"col\">Location</th>") LINE_TERMINATOR;
                HtmlString += TEXT("            <th scope=\"col\">Between</th>") LINE_TERMINATOR;
                HtmlString += TEXT("            <th scope=\"col\">And</th>") LINE_TERMINATOR;
                HtmlString += TEXT("            <th scope=\"col\">Game</th>") LINE_TERMINATOR;
                HtmlString += TEXT("            <th scope=\"col\">Render</th>") LINE_TERMINATOR;
                HtmlString += TEXT("            <th scope=\"col\">GPU</th>") LINE_TERMINATOR;
                HtmlString += TEXT("            <th scope=\"col\">Screenshot</th>") LINE_TERMINATOR;
                HtmlString += TEXT("          </tr>") LINE_TERMINATOR;
                HtmlString += TEXT("        </thead>") LINE_TERMINATOR;
                HtmlString += TEXT("        <tbody>") LINE_TERMINATOR;

                for (const FDaeTestPerformanceBudgetViolation& BudgetViolation :
                     Data->BudgetViolations)
                {
                    // Copy screenshot.
                    IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();

                    FString OldScreenshotPath = BudgetViolation.ScreenshotPath;
                    FString ScreenshotFilename = FPaths::GetCleanFilename(OldScreenshotPath);
                    FString NewScreenshotPath = FPaths::Combine(ReportPath, ScreenshotFilename);

                    UE_LOG(LogDaeTest, Display, TEXT("Copying %s to %s."), *OldScreenshotPath,
                           *NewScreenshotPath);

                    PlatformFile.CopyFile(*NewScreenshotPath, *OldScreenshotPath);

                    // Write budget violation.
                    HtmlString += TEXT("          <tr>") LINE_TERMINATOR;

                    HtmlString += FString::Printf(TEXT("            <td>%s</td>"),
                                                  *BudgetViolation.CurrentLocation.ToString())
                                  + LINE_TERMINATOR;
                    HtmlString += FString::Printf(TEXT("            <td>%s</td>"),
                                                  *BudgetViolation.PreviousTargetPointName)
                                  + LINE_TERMINATOR;
                    HtmlString += FString::Printf(TEXT("            <td>%s</td>"),
                                                  *BudgetViolation.NextTargetPointName)
                                  + LINE_TERMINATOR;
                    HtmlString += FString::Printf(TEXT("            <td>%s&nbsp;ms</td>"),
                                                  *FormatTime(BudgetViolation.GameThreadTime))
                                  + LINE_TERMINATOR;
                    HtmlString += FString::Printf(TEXT("            <td>%s&nbsp;ms</td>"),
                                                  *FormatTime(BudgetViolation.RenderThreadTime))
                                  + LINE_TERMINATOR;
                    HtmlString += FString::Printf(TEXT("            <td>%s&nbsp;ms</td>"),
                                                  *FormatTime(BudgetViolation.GPUTime))
                                  + LINE_TERMINATOR;
                    HtmlString += FString::Printf(TEXT("            <td><a href=\"%s\" "
                                                       "target=\"_blank\"><img src=\"%s\" "
                                                       "class=\"img-fluid\" alt=\"%s\"/></a></td>"),
                                                  *ScreenshotFilename, *ScreenshotFilename,
                                                  *ScreenshotFilename)
                                  + LINE_TERMINATOR;
                    HtmlString += TEXT("          </tr>") LINE_TERMINATOR;
                }

                HtmlString += TEXT("        </tbody>") LINE_TERMINATOR;
                HtmlString += TEXT("      </table>") LINE_TERMINATOR;
            }
        }
    }

    HtmlString += TEXT("    </div>") LINE_TERMINATOR;
    HtmlString += TEXT("  </body>") LINE_TERMINATOR;
    HtmlString += TEXT("</html>") LINE_TERMINATOR;

    UE_LOG(LogDaeTest, Verbose, TEXT("Test report:\r\n%s"), *HtmlString);
    UE_LOG(LogDaeTest, Display, TEXT("Writing test report to: %s"), *HtmlReportPath);

    FFileHelper::SaveStringToFile(HtmlString, *HtmlReportPath);
}

FString FDaeTestReportWriterPerformance::FormatTime(float Time) const
{
    return UKismetTextLibrary::Conv_FloatToText(Time, ERoundingMode::HalfToEven, false, false, 1,
                                                324, 2, 2)
        .ToString();
}
