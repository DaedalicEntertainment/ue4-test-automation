#include "DaeGauntletTestActor.h"

void ADaeGauntletTestActor::RunTest()
{
    NotifyOnTestStarted();
}

void ADaeGauntletTestActor::TestSuccessful()
{
    OnTestSuccessful.Broadcast(this);
}

void ADaeGauntletTestActor::TestFailed()
{
    OnTestFailed.Broadcast(this);
}

void ADaeGauntletTestActor::NotifyOnTestStarted()
{
    ReceiveOnTestStarted();
}
