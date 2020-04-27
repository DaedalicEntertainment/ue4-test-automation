#include "DaeTestActor.h"
#include "DaeTestLogCategory.h"

const FString ADaeTestActor::ErrorMessageFormat =
    TEXT("Assertion failed - {0} - Expected: {1}, but was: {2}");

void ADaeTestActor::RunTest()
{
    bHasResult = false;

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

void ADaeTestActor::AssertFail(const FString& What)
{
    NotifyOnTestFailed(What);
}

void ADaeTestActor::AssertTrue(const FString& What, bool bValue)
{
    if (!bValue)
    {
        FString Message = FString::Format(*ErrorMessageFormat, {What, TEXT("True"), TEXT("False")});
        NotifyOnTestFailed(Message);
    }
}

void ADaeTestActor::AssertFalse(const FString& What, bool bValue)
{
    if (bValue)
    {
        FString Message = FString::Format(*ErrorMessageFormat, {What, TEXT("False"), TEXT("True")});
        NotifyOnTestFailed(Message);
    }
}

void ADaeTestActor::AssertEqualsVector(const FString& What, const FVector& Actual,
                                       const FVector& Expected)
{
    if (!Actual.Equals(Expected))
    {
        FString Message =
            FString::Format(*ErrorMessageFormat, {What, Expected.ToString(), Actual.ToString()});
        NotifyOnTestFailed(Message);
    }
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
