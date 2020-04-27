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

        public override void ApplyToConfig(UnrealAppConfig AppConfig, UnrealSessionRole ConfigRole, IEnumerable<UnrealSessionRole> OtherRoles)
        {
            base.ApplyToConfig(AppConfig, ConfigRole, OtherRoles);

            if (!string.IsNullOrEmpty(JUnitReportPath))
            {
                AppConfig.CommandLine += string.Format(" JUnitReportPath=\"{0}\"", JUnitReportPath);
            }
        }
    }
}
