#include "DaeTestActor.h"
#include "DaeTestLogCategory.h"
#include "DaeTestTriggerBox.h"
#include <InputCoreTypes.h>
#include <GameFramework/InputSettings.h>
#include <GameFramework/PlayerController.h>
#include <GameFramework/PlayerInput.h>

const FString ADaeTestActor::ErrorMessageFormat =
    TEXT("Assertion failed - {0} - Expected: {1}, but was: {2}");

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

void ADaeTestActor::ApplyInputAction(const FName& ActionName)
{
    APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);

    const UInputSettings* InputSettings = GetDefault<UInputSettings>();

    for (const FInputActionKeyMapping& Mapping : InputSettings->GetActionMappings())
    {
        if (Mapping.ActionName == ActionName)
        {
            PlayerController->InputKey(Mapping.Key, EInputEvent::IE_Pressed, 0.0f, false);
            return;
        }
    }

    UE_LOG(LogDaeTest, Error, TEXT("%s - Input action not found: %s"), *GetName(),
           *ActionName.ToString());
}

void ADaeTestActor::ApplyInputAxis(const FName& AxisName, float AxisValue /*= 1.0f*/)
{
    APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);

    const UInputSettings* InputSettings = GetDefault<UInputSettings>();

    for (const FInputAxisKeyMapping& Mapping : InputSettings->GetAxisMappings())
    {
        if (Mapping.AxisName == AxisName)
        {
            PlayerController->InputAxis(Mapping.Key, AxisValue, 0.0f, 1, false);
            return;
        }
    }

    UE_LOG(LogDaeTest, Error, TEXT("%s - Input axis not found: %s"), *GetName(),
           *AxisName.ToString());
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

void ADaeTestActor::AssertWasTriggered(ADaeTestTriggerBox* TestTriggerBox)
{
    if (!IsValid(TestTriggerBox))
    {
        NotifyOnTestFailed(TEXT("Invalid test trigger box in assertion"));
        return;
    }

    if (!TestTriggerBox->WasTriggered())
    {
        FString Message =
            FString::Format(TEXT("Assertion failed - Trigger box {0} wasn't triggered"),
                            {*TestTriggerBox->GetName()});
        NotifyOnTestFailed(Message);
        return;
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
