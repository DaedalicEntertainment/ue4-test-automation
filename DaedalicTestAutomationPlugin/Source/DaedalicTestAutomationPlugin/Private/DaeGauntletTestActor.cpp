#include "DaeGauntletTestActor.h"
#include "DaeTestLogCategory.h"

void ADaeGauntletTestActor::RunTest()
{
    bHasResult = false;

    NotifyOnArrange();
    NotifyOnAct();
}

void ADaeGauntletTestActor::FinishAct()
{
    if (bHasResult)
    {
        UE_LOG(LogDaeTest, Error,
               TEXT(
                   "Test %s already has a result. Make sure not to call FinishAct more than once."),
               *GetName());
        return;
    }

    NotifyOnAssert();

    if (!bHasResult)
    {
        NotifyOnTestSuccessful();
    }
}

void ADaeGauntletTestActor::AssertFail()
{
    NotifyOnTestFailed();
}

void ADaeGauntletTestActor::NotifyOnTestSuccessful()
{
    if (bHasResult)
    {
        return;
    }

    bHasResult = true;

    OnTestSuccessful.Broadcast(this);
}

void ADaeGauntletTestActor::NotifyOnTestFailed()
{
    if (bHasResult)
    {
        return;
    }

    bHasResult = true;

    OnTestFailed.Broadcast(this);
}

void ADaeGauntletTestActor::NotifyOnArrange()
{
    ReceiveOnArrange();
}

void ADaeGauntletTestActor::NotifyOnAct()
{
    ReceiveOnAct();
}

void ADaeGauntletTestActor::NotifyOnAssert()
{
    ReceiveOnAssert();
}

void ADaeGauntletTestActor::ReceiveOnAct_Implementation()
{
    FinishAct();
}
