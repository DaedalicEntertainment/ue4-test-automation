#include "DaeTestAssertBlueprintFunctionLibrary.h"
#include "DaeTestActor.h"
#include "DaeTestLogCategory.h"
#include "DaeTestTriggerBox.h"
#include <Blueprint/UserWidget.h>
#include <Kismet/KismetMathLibrary.h>

const FString UDaeTestAssertBlueprintFunctionLibrary::ErrorMessageFormat =
    TEXT("Assertion failed - {0} - Expected: {1}, but was: {2}");

void UDaeTestAssertBlueprintFunctionLibrary::AssertFail(UObject* Context, const FString& What)
{
    OnTestFailed(Context, What);
}

void UDaeTestAssertBlueprintFunctionLibrary::AssertTrue(UObject* Context, const FString& What,
                                                        bool bValue)
{
    if (!bValue)
    {
        FString Message = FString::Format(*ErrorMessageFormat, {What, TEXT("True"), TEXT("False")});
        OnTestFailed(Context, Message);
    }
}

void UDaeTestAssertBlueprintFunctionLibrary::AssertFalse(UObject* Context, const FString& What,
                                                         bool bValue)
{
    if (bValue)
    {
        FString Message = FString::Format(*ErrorMessageFormat, {What, TEXT("False"), TEXT("True")});
        OnTestFailed(Context, Message);
    }
}

void UDaeTestAssertBlueprintFunctionLibrary::AssertValid(UObject* Context, const FString& What,
                                                         UObject* Object)
{
    if (!IsValid(Object))
    {
        FString Message =
            FString::Format(TEXT("Assertion failed - {0} - Expected: valid, but was: invalid"),
                            {What});
        OnTestFailed(Context, Message);
        return;
    }
}

void UDaeTestAssertBlueprintFunctionLibrary::AssertInvalid(UObject* Context, const FString& What,
                                                           UObject* Object)
{
    if (IsValid(Object))
    {
        FString Message =
            FString::Format(TEXT("Assertion failed - {0} - Expected: invalid, but was: valid"),
                            {What});
        OnTestFailed(Context, Message);
        return;
    }
}

void UDaeTestAssertBlueprintFunctionLibrary::AssertWasTriggered(UObject* Context,
                                                                ADaeTestTriggerBox* TestTriggerBox)
{
    if (!IsValid(TestTriggerBox))
    {
        OnTestFailed(Context, TEXT("Invalid test trigger box in assertion"));
        return;
    }

    if (!TestTriggerBox->WasTriggered())
    {
        FString Message =
            FString::Format(TEXT("Assertion failed - Trigger box {0} wasn't triggered"),
                            {TestTriggerBox->GetName()});
        OnTestFailed(Context, Message);
        return;
    }
}

void UDaeTestAssertBlueprintFunctionLibrary::AssertEqualsVector(UObject* Context,
                                                                const FString& What,
                                                                const FVector& Actual,
                                                                const FVector& Expected)
{
    if (!Actual.Equals(Expected))
    {
        FString Message =
            FString::Format(*ErrorMessageFormat, {What, Expected.ToString(), Actual.ToString()});
        OnTestFailed(Context, Message);
    }
}

void UDaeTestAssertBlueprintFunctionLibrary::AssertInRangeFloat(UObject* Context,
                                                                const FString& What, float Value,
                                                                float MinInclusive,
                                                                float MaxInclusive)
{
    if (!UKismetMathLibrary::InRange_FloatFloat(Value, MinInclusive, MaxInclusive))
    {
        FString Message = FString::Format(
            TEXT("Assertion failed - {0} - Expected: between {1} and {2}, but was: {3}"),
            {What, MinInclusive, MaxInclusive, Value});
        OnTestFailed(Context, Message);
    }
}

void UDaeTestAssertBlueprintFunctionLibrary::AssertWidgetIsVisible(UObject* Context,
                                                                   const FString& What,
                                                                   UUserWidget* Widget)
{
    if (!IsValid(Widget))
    {
        FString Message =
            FString::Format(TEXT("Assertion failed - {0} - Widget is not valid"), {What});
        OnTestFailed(Context, Message);
        return;
    }

    if (!Widget->IsInViewport())
    {
        FString Message = FString::Format(
            TEXT("Assertion failed - {0} - Widget hasn't been added to the viewport"), {What});
        OnTestFailed(Context, Message);
        return;
    }

    if (!Widget->IsVisible())
    {
        FString Message = FString::Format(TEXT("Assertion failed - {0} - Widget isn't visible, hit "
                                               "test visible or self hit test visible"),
                                          {What});
        OnTestFailed(Context, Message);
        return;
    }
}

void UDaeTestAssertBlueprintFunctionLibrary::OnTestFailed(UObject* Context, const FString& Message)
{
    ADaeTestActor* TestActor = Cast<ADaeTestActor>(Context);

    if (IsValid(TestActor))
    {
        TestActor->NotifyOnTestFailed(Message);
    }
    else
    {
        UE_LOG(LogDaeTest, Error, TEXT("%s"), *Message);
    }
}
