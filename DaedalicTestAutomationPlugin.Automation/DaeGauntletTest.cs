using EpicGame;
using Gauntlet;
using UE4Game;

namespace DaedalicTestAutomationPlugin.Automation
{
    public class DaeGauntletTest : UnrealTestNode<EpicGameTestConfig>
    {
        public DaeGauntletTest(UnrealTestContext InContext) : base(InContext)
        {
        }

        public override EpicGameTestConfig GetConfiguration()
        {
            EpicGameTestConfig Config = base.GetConfiguration();

            // Start a single instance of the game.
            UnrealTestRole ClientRole = Config.RequireRole(UnrealTargetRole.Client);
            ClientRole.Controllers.Add("DaeGauntletTestController");

            // Ignore user account management.
            Config.NoMCP = true;

            return Config;
        }
    }
}
