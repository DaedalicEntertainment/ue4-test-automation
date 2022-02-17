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
            Config.MaxDuration = 1800;
            ClientRole.Controllers.Add("DaeGauntletTestController");

            // Ignore user account management.
            Config.NoMCP = true;

            return Config;
        }
    }
}
