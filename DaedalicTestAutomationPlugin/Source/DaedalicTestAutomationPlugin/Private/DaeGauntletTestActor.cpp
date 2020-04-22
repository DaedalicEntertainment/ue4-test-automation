#include "DaeGauntletTestActor.h"
#include "DaeTestLogCategory.h"

const FString ADaeGauntletTestActor::ErrorMessageFormat =
    TEXT("Assertion failed - {0} - Expected: {1}, but was: {2}");

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

void ADaeGauntletTestActor::AssertFail(const FString& What)
{
    NotifyOnTestFailed(What);
}

void ADaeGauntletTestActor::AssertTrue(const FString& What, bool bValue)
{
    if (!bValue)
    {
        FString Message = FString::Format(*ErrorMessageFormat, {What, TEXT("True"), TEXT("False")});
        NotifyOnTestFailed(Message);
    }
}

void ADaeGauntletTestActor::AssertFalse(const FString& What, bool bValue)
{
    if (bValue)
    {
        FString Message = FString::Format(*ErrorMessageFormat, {What, TEXT("False"), TEXT("True")});
        NotifyOnTestFailed(Message);
    }
}

void ADaeGauntletTestActor::AssertEqualsVector(const FString& What, const FVector& Actual,
                                               const FVector& Expected)
{
    if (!Actual.Equals(Expected))
    {
        FString Message =
            FString::Format(*ErrorMessageFormat, {What, Expected.ToString(), Actual.ToString()});
        NotifyOnTestFailed(Message);
    }
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

void ADaeGauntletTestActor::NotifyOnTestFailed(const FString& Message)
{
    if (bHasResult)
    {
        return;
    }

    bHasResult = true;

    UE_LOG(LogDaeTest, Error, TEXT("%s"), *Message);

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
