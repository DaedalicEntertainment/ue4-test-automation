#include "DaeTestActor.h"
#include "DaeTestLogCategory.h"

ADaeTestActor::ADaeTestActor(
    const FObjectInitializer& ObjectInitializer /*= FObjectInitializer::Get()*/)
    : Super(ObjectInitializer)
{
    TimeoutInSeconds = 30.0f;
}

void ADaeTestActor::RunTest(UObject* TestParameter)
{
    CurrentParameter = TestParameter;
    bHasResult = false;

    if (!SkipReason.IsEmpty())
    {
        NotifyOnTestSkipped();
        return;
    }

    NotifyOnArrange(CurrentParameter);
    NotifyOnAct(CurrentParameter);
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

    NotifyOnAssert(CurrentParameter);

    if (!bHasResult)
    {
        NotifyOnTestSuccessful();
    }
}

float ADaeTestActor::GetTimeoutInSeconds() const
{
    return TimeoutInSeconds;
}

TArray<UObject*> ADaeTestActor::GetParameters() const
{
    return Parameters;
}

UObject* ADaeTestActor::GetCurrentParameter() const
{
    return CurrentParameter;
}

void ADaeTestActor::NotifyOnTestSuccessful()
{
    if (bHasResult)
    {
        return;
    }

    bHasResult = true;

    OnTestSuccessful.Broadcast(this, CurrentParameter);
}

void ADaeTestActor::NotifyOnTestFailed(const FString& Message)
{
    if (bHasResult)
    {
        return;
    }

    bHasResult = true;

    UE_LOG(LogDaeTest, Error, TEXT("%s"), *Message);

    OnTestFailed.Broadcast(this, CurrentParameter, Message);
}

void ADaeTestActor::NotifyOnTestSkipped()
{
    if (bHasResult)
    {
        return;
    }

    bHasResult = true;

    OnTestSkipped.Broadcast(this, CurrentParameter, SkipReason);
}

void ADaeTestActor::NotifyOnArrange(UObject* Parameter)
{
    ReceiveOnArrange(Parameter);
}

void ADaeTestActor::NotifyOnAct(UObject* Parameter)
{
    ReceiveOnAct(Parameter);
}

void ADaeTestActor::NotifyOnAssert(UObject* Parameter)
{
    ReceiveOnAssert(Parameter);
}

void ADaeTestActor::ReceiveOnAct_Implementation(UObject* Parameter)
{
    FinishAct();
}
