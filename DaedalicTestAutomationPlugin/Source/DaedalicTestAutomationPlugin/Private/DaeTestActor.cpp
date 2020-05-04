#include "DaeTestActor.h"
#include "DaeTestLogCategory.h"

ADaeTestActor::ADaeTestActor(
    const FObjectInitializer& ObjectInitializer /*= FObjectInitializer::Get()*/)
    : Super(ObjectInitializer)
{
    TimeoutInSeconds = 30.0f;
}

void ADaeTestActor::RunTest()
{
    bHasResult = false;

    if (!SkipReason.IsEmpty())
    {
        NotifyOnTestSkipped();
        return;
    }

    NotifyOnArrange();
    NotifyOnAct();
}

void ADaeTestActor::FinishAct()
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

float ADaeTestActor::GetTimeoutInSeconds() const
{
    return TimeoutInSeconds;
}

void ADaeTestActor::NotifyOnTestSuccessful()
{
    if (bHasResult)
    {
        return;
    }

    bHasResult = true;

    OnTestSuccessful.Broadcast(this);
}

void ADaeTestActor::NotifyOnTestFailed(const FString& Message)
{
    if (bHasResult)
    {
        return;
    }

    bHasResult = true;

    UE_LOG(LogDaeTest, Error, TEXT("%s"), *Message);

    OnTestFailed.Broadcast(this, Message);
}

void ADaeTestActor::NotifyOnTestSkipped()
{
    if (bHasResult)
    {
        return;
    }

    bHasResult = true;

    OnTestSkipped.Broadcast(this, SkipReason);
}

void ADaeTestActor::NotifyOnArrange()
{
    ReceiveOnArrange();
}

void ADaeTestActor::NotifyOnAct()
{
    ReceiveOnAct();
}

void ADaeTestActor::NotifyOnAssert()
{
    ReceiveOnAssert();
}

void ADaeTestActor::ReceiveOnAct_Implementation()
{
    FinishAct();
}
