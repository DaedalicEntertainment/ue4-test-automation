using Gauntlet;
using System.Collections.Generic;

namespace DaedalicTestAutomationPlugin.Automation
{
    public class DaeTestConfig : EpicGame.EpicGameTestConfig
    {
        /// <summary>
		/// Where to write a JUnit XML report to.
		/// </summary>
		[AutoParam]
        public string JUnitReportPath;

        /// <summary>
        /// Where to write test reports to.
        /// </summary>
        [AutoParam]
        public string ReportPath;

        /// <summary>
        /// Which single test to run, instead of all available tests.
        /// </summary>
        [AutoParam]
        public string TestName;

        public override void ApplyToConfig(UnrealAppConfig AppConfig, UnrealSessionRole ConfigRole, IEnumerable<UnrealSessionRole> OtherRoles)
        {
            base.ApplyToConfig(AppConfig, ConfigRole, OtherRoles);

            if (!string.IsNullOrEmpty(JUnitReportPath))
            {
                AppConfig.CommandLine += string.Format(" -JUnitReportPath=\"{0}\"", JUnitReportPath);
            }

            if (!string.IsNullOrEmpty(ReportPath))
            {
                AppConfig.CommandLine += string.Format(" -ReportPath=\"{0}\"", ReportPath);
            }

            if (!string.IsNullOrEmpty(TestName))
            {
                AppConfig.CommandLine += string.Format(" -TestName=\"{0}\"", TestName);
            }
        }
    }
}
