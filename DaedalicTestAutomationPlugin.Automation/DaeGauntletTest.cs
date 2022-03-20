using Gauntlet;

namespace DaedalicTestAutomationPlugin.Automation
{
    public class DaeGauntletTest : UnrealTestNode<DaeTestConfig>
    {
        public DaeGauntletTest(UnrealTestContext InContext) : base(InContext)
        {
        }

        public override DaeTestConfig GetConfiguration()
        {
            DaeTestConfig Config = base.GetConfiguration();

            // Start a single instance of the game.
            UnrealTestRole ClientRole = Config.RequireRole(UnrealTargetRole.Client);
            Config.MaxDuration = 2 * 60 * 60; // Timout calculation: Hours * Minutes * Seconds
            ClientRole.Controllers.Add("DaeGauntletTestController");

            // Ignore user account management.
            Config.NoMCP = true;

            return Config;
        }
    }
}
