#include "DaeTestAssertBlueprintFunctionLibrary.h"
#include "DaeTestActor.h"
#include "DaeTestLogCategory.h"
#include "DaeTestTriggerBox.h"
#include <Blueprint/UserWidget.h>
#include <Components/Image.h>
#include <Components/PanelWidget.h>
#include <Components/RichTextBlock.h>
#include <Components/TextBlock.h>
#include <Kismet/KismetMathLibrary.h>
#include <Styling/SlateBrush.h>

const FString UDaeTestAssertBlueprintFunctionLibrary::ErrorMessageFormatEqual =
    TEXT("Assertion failed - {0} - Expected: {1}, but was: {2}");

const FString UDaeTestAssertBlueprintFunctionLibrary::ErrorMessageFormatNotEqual =
    TEXT("Assertion failed - {0} - Was {1}, but should not be.");

const FString UDaeTestAssertBlueprintFunctionLibrary::ErrorMessageFormatInRange =
    TEXT("Assertion failed - {0} - Expected: between {1} and {2}, but was: {3}");

const FString UDaeTestAssertBlueprintFunctionLibrary::ErrorMessageFormatNotInRange =
    TEXT("Assertion failed - {0} - Expected: not between {1} and {2}, but was: {3}");

void UDaeTestAssertBlueprintFunctionLibrary::AssertFail(const FString& What,
                                                        UObject* Context /*= nullptr*/)
{
    OnTestFailed(Context, What);
}

void UDaeTestAssertBlueprintFunctionLibrary::AssertTrue(const FString& What, bool bValue,
                                                        UObject* Context /*= nullptr*/)
{
    if (!bValue)
    {
        FString Message =
            FString::Format(*ErrorMessageFormatEqual, {What, TEXT("True"), TEXT("False")});
        OnTestFailed(Context, Message);
    }
}

void UDaeTestAssertBlueprintFunctionLibrary::AssertFalse(const FString& What, bool bValue,
                                                         UObject* Context /*= nullptr*/)
{
    if (bValue)
    {
        FString Message =
            FString::Format(*ErrorMessageFormatEqual, {What, TEXT("False"), TEXT("True")});
        OnTestFailed(Context, Message);
    }
}

void UDaeTestAssertBlueprintFunctionLibrary::AssertValid(const FString& What, UObject* Object,
                                                         UObject* Context /*= nullptr*/)
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

void UDaeTestAssertBlueprintFunctionLibrary::AssertInvalid(const FString& What, UObject* Object,
                                                           UObject* Context /*= nullptr*/)
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

void UDaeTestAssertBlueprintFunctionLibrary::AssertWasTriggered(ADaeTestTriggerBox* TestTriggerBox,
                                                                UObject* Context /*= nullptr*/)
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

void UDaeTestAssertBlueprintFunctionLibrary::AssertWasNotTriggered(
    ADaeTestTriggerBox* TestTriggerBox, UObject* Context /*= nullptr*/)
{
    if (!IsValid(TestTriggerBox))
    {
        OnTestFailed(Context, TEXT("Invalid test trigger box in assertion"));
        return;
    }

    if (TestTriggerBox->WasTriggered())
    {
        FString Message = FString::Format(TEXT("Assertion failed - Trigger box {0} was triggered"),
                                          {TestTriggerBox->GetName()});
        OnTestFailed(Context, Message);
        return;
    }
}

void UDaeTestAssertBlueprintFunctionLibrary::AssertEqualByte(const FString& What, uint8 Actual,
                                                             uint8 Expected,
                                                             UObject* Context /*= nullptr*/)
{
    AssertEqual(Context, What, Actual, Expected);
}

void UDaeTestAssertBlueprintFunctionLibrary::AssertNotEqualByte(const FString& What, uint8 Actual,
                                                                uint8 Unexpected,
                                                                UObject* Context /*= nullptr*/)
{
    AssertNotEqual(Context, What, Actual, Unexpected);
}

void UDaeTestAssertBlueprintFunctionLibrary::AssertEqualInt32(const FString& What, int32 Actual,
                                                              int32 Expected,
                                                              UObject* Context /*= nullptr*/)
{
    AssertEqual(Context, What, Actual, Expected);
}

void UDaeTestAssertBlueprintFunctionLibrary::AssertNotEqualInt32(const FString& What, int32 Actual,
                                                                 int32 Unexpected,
                                                                 UObject* Context /*= nullptr*/)
{
    AssertNotEqual(Context, What, Actual, Unexpected);
}

void UDaeTestAssertBlueprintFunctionLibrary::AssertEqualInt64(const FString& What, int64 Actual,
                                                              int64 Expected,
                                                              UObject* Context /*= nullptr*/)
{
    AssertEqual(Context, What, Actual, Expected);
}

void UDaeTestAssertBlueprintFunctionLibrary::AssertNotEqualInt64(const FString& What, int64 Actual,
                                                                 int64 Unexpected,
                                                                 UObject* Context /*= nullptr*/)
{
    AssertNotEqual(Context, What, Actual, Unexpected);
}

void UDaeTestAssertBlueprintFunctionLibrary::AssertEqualFloat(const FString& What, float Actual,
                                                              float Expected,
                                                              UObject* Context /*= nullptr*/)
{
    if (!FMath::IsNearlyEqual(Actual, Expected))
    {
        FString Message = FString::Format(*ErrorMessageFormatEqual, {What, Expected, Actual});
        OnTestFailed(Context, Message);
    }
}

void UDaeTestAssertBlueprintFunctionLibrary::AssertNotEqualFloat(const FString& What, float Actual,
                                                                 float Unexpected,
                                                                 UObject* Context /*= nullptr*/)
{
    if (FMath::IsNearlyEqual(Actual, Unexpected))
    {
        FString Message = FString::Format(*ErrorMessageFormatNotEqual, {What, Unexpected});
        OnTestFailed(Context, Message);
    }
}

void UDaeTestAssertBlueprintFunctionLibrary::AssertEqualName(const FString& What,
                                                             const FName& Actual,
                                                             const FName& Expected,
                                                             UObject* Context /*= nullptr*/)
{
    if (!Actual.IsEqual(Expected))
    {
        FString Message = FString::Format(*ErrorMessageFormatEqual,
                                          {What, Expected.ToString(), Actual.ToString()});
        OnTestFailed(Context, Message);
    }
}

void UDaeTestAssertBlueprintFunctionLibrary::AssertNotEqualName(const FString& What,
                                                                const FName& Actual,
                                                                const FName& Unexpected,
                                                                UObject* Context /*= nullptr*/)
{
    if (Actual.IsEqual(Unexpected))
    {
        FString Message =
            FString::Format(*ErrorMessageFormatNotEqual, {What, Unexpected.ToString()});
        OnTestFailed(Context, Message);
    }
}

void UDaeTestAssertBlueprintFunctionLibrary::AssertEqualString(const FString& What,
                                                               const FString& Actual,
                                                               const FString& Expected,
                                                               UObject* Context /*= nullptr*/)
{
    if (!Actual.Equals(Expected))
    {
        FString Message = FString::Format(*ErrorMessageFormatEqual, {What, Expected, Actual});
        OnTestFailed(Context, Message);
    }
}

void UDaeTestAssertBlueprintFunctionLibrary::AssertNotEqualString(const FString& What,
                                                                  const FString& Actual,
                                                                  const FString& Unexpected,
                                                                  UObject* Context /*= nullptr*/)
{
    if (Actual.Equals(Unexpected))
    {
        FString Message = FString::Format(*ErrorMessageFormatNotEqual, {What, Unexpected});
        OnTestFailed(Context, Message);
    }
}

void UDaeTestAssertBlueprintFunctionLibrary::AssertEqualText(const FString& What,
                                                             const FText& Actual,
                                                             const FText& Expected,
                                                             UObject* Context /*= nullptr*/)
{
    if (!Actual.EqualTo(Expected))
    {
        FString Message = FString::Format(*ErrorMessageFormatEqual,
                                          {What, Expected.ToString(), Actual.ToString()});
        OnTestFailed(Context, Message);
    }
}

void UDaeTestAssertBlueprintFunctionLibrary::AssertNotEqualText(const FString& What,
                                                                const FText& Actual,
                                                                const FText& Unexpected,
                                                                UObject* Context /*= nullptr*/)
{
    if (Actual.EqualTo(Unexpected))
    {
        FString Message =
            FString::Format(*ErrorMessageFormatNotEqual, {What, Unexpected.ToString()});
        OnTestFailed(Context, Message);
    }
}

void UDaeTestAssertBlueprintFunctionLibrary::AssertEqualVector(const FString& What,
                                                               const FVector& Actual,
                                                               const FVector& Expected,
                                                               UObject* Context /*= nullptr*/)
{
    if (!Actual.Equals(Expected))
    {
        FString Message = FString::Format(*ErrorMessageFormatEqual,
                                          {What, Expected.ToString(), Actual.ToString()});
        OnTestFailed(Context, Message);
    }
}

void UDaeTestAssertBlueprintFunctionLibrary::AssertNotEqualVector(const FString& What,
                                                                  const FVector& Actual,
                                                                  const FVector& Unexpected,
                                                                  UObject* Context /*= nullptr*/)
{
    if (Actual.Equals(Unexpected))
    {
        FString Message =
            FString::Format(*ErrorMessageFormatNotEqual, {What, Unexpected.ToString()});
        OnTestFailed(Context, Message);
    }
}

void UDaeTestAssertBlueprintFunctionLibrary::AssertEqualRotator(const FString& What,
                                                                const FRotator& Actual,
                                                                const FRotator& Expected,
                                                                UObject* Context /*= nullptr*/)
{
    if (!Actual.Equals(Expected))
    {
        FString Message = FString::Format(*ErrorMessageFormatEqual,
                                          {What, Expected.ToString(), Actual.ToString()});
        OnTestFailed(Context, Message);
    }
}

void UDaeTestAssertBlueprintFunctionLibrary::AssertNotEqualRotator(const FString& What,
                                                                   const FRotator& Actual,
                                                                   const FRotator& Unexpected,
                                                                   UObject* Context /*= nullptr*/)
{
    if (Actual.Equals(Unexpected))
    {
        FString Message =
            FString::Format(*ErrorMessageFormatNotEqual, {What, Unexpected.ToString()});
        OnTestFailed(Context, Message);
    }
}

void UDaeTestAssertBlueprintFunctionLibrary::AssertEqualTransform(const FString& What,
                                                                  const FTransform& Actual,
                                                                  const FTransform& Expected,
                                                                  UObject* Context /*= nullptr*/)
{
    if (!Actual.Equals(Expected))
    {
        FString Message = FString::Format(*ErrorMessageFormatEqual,
                                          {What, Expected.ToString(), Actual.ToString()});
        OnTestFailed(Context, Message);
    }
}

void UDaeTestAssertBlueprintFunctionLibrary::AssertNotEqualTransform(const FString& What,
                                                                     const FTransform& Actual,
                                                                     const FTransform& Unexpected,
                                                                     UObject* Context /*= nullptr*/)
{
    if (Actual.Equals(Unexpected))
    {
        FString Message =
            FString::Format(*ErrorMessageFormatNotEqual, {What, Unexpected.ToString()});
        OnTestFailed(Context, Message);
    }
}

void UDaeTestAssertBlueprintFunctionLibrary::AssertInRangeByte(const FString& What, uint8 Value,
                                                               uint8 MinInclusive,
                                                               uint8 MaxInclusive,
                                                               UObject* Context /*= nullptr*/)
{
    AssertInRangeInt32(What, Value, MinInclusive, MaxInclusive, Context);
}

void UDaeTestAssertBlueprintFunctionLibrary::AssertNotInRangeByte(const FString& What, uint8 Value,
                                                                  uint8 MinInclusive,
                                                                  uint8 MaxInclusive,
                                                                  UObject* Context /*= nullptr*/)
{
    AssertNotInRangeInt32(What, Value, MinInclusive, MaxInclusive, Context);
}

void UDaeTestAssertBlueprintFunctionLibrary::AssertInRangeInt32(const FString& What, int32 Value,
                                                                int32 MinInclusive,
                                                                int32 MaxInclusive,
                                                                UObject* Context /*= nullptr*/)
{
    if (!UKismetMathLibrary::InRange_IntInt(Value, MinInclusive, MaxInclusive))
    {
        FString Message =
            FString::Format(*ErrorMessageFormatInRange, {What, MinInclusive, MaxInclusive, Value});
        OnTestFailed(Context, Message);
    }
}

void UDaeTestAssertBlueprintFunctionLibrary::AssertNotInRangeInt32(const FString& What, int32 Value,
                                                                   int32 MinInclusive,
                                                                   int32 MaxInclusive,
                                                                   UObject* Context /*= nullptr*/)
{
    if (UKismetMathLibrary::InRange_IntInt(Value, MinInclusive, MaxInclusive))
    {
        FString Message = FString::Format(*ErrorMessageFormatNotInRange,
                                          {What, MinInclusive, MaxInclusive, Value});
        OnTestFailed(Context, Message);
    }
}

void UDaeTestAssertBlueprintFunctionLibrary::AssertInRangeInt64(const FString& What, int64 Value,
                                                                int64 MinInclusive,
                                                                int64 MaxInclusive,
                                                                UObject* Context /*= nullptr*/)
{
    if (!UKismetMathLibrary::InRange_Int64Int64(Value, MinInclusive, MaxInclusive))
    {
        FString Message =
            FString::Format(*ErrorMessageFormatInRange, {What, MinInclusive, MaxInclusive, Value});
        OnTestFailed(Context, Message);
    }
}

void UDaeTestAssertBlueprintFunctionLibrary::AssertNotInRangeInt64(const FString& What, int64 Value,
                                                                   int64 MinInclusive,
                                                                   int64 MaxInclusive,
                                                                   UObject* Context /*= nullptr*/)
{
    if (UKismetMathLibrary::InRange_Int64Int64(Value, MinInclusive, MaxInclusive))
    {
        FString Message = FString::Format(*ErrorMessageFormatNotInRange,
                                          {What, MinInclusive, MaxInclusive, Value});
        OnTestFailed(Context, Message);
    }
}

void UDaeTestAssertBlueprintFunctionLibrary::AssertInRangeFloat(const FString& What, float Value,
                                                                float MinInclusive,
                                                                float MaxInclusive,
                                                                UObject* Context /*= nullptr*/)
{
    if (!UKismetMathLibrary::InRange_FloatFloat(Value, MinInclusive, MaxInclusive))
    {
        FString Message =
            FString::Format(*ErrorMessageFormatInRange, {What, MinInclusive, MaxInclusive, Value});
        OnTestFailed(Context, Message);
    }
}

void UDaeTestAssertBlueprintFunctionLibrary::AssertNotInRangeFloat(const FString& What, float Value,
                                                                   float MinInclusive,
                                                                   float MaxInclusive,
                                                                   UObject* Context /*= nullptr*/)
{
    if (UKismetMathLibrary::InRange_FloatFloat(Value, MinInclusive, MaxInclusive))
    {
        FString Message = FString::Format(*ErrorMessageFormatNotInRange,
                                          {What, MinInclusive, MaxInclusive, Value});
        OnTestFailed(Context, Message);
    }
}

void UDaeTestAssertBlueprintFunctionLibrary::AssertWidgetIsVisible(const FString& What,
                                                                   UUserWidget* Widget,
                                                                   UObject* Context /*= nullptr*/)
{
    if (!IsValid(Widget))
    {
        FString Message =
            FString::Format(TEXT("Assertion failed - {0} - Widget is not valid"), {What});
        OnTestFailed(Context, Message);
        return;
    }

    if (!Widget->IsInViewport() && !IsValid(Widget->GetParent()))
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

void UDaeTestAssertBlueprintFunctionLibrary::AssertTextIsSet(const FString& What,
                                                             UTextBlock* TextBlock,
                                                             UObject* Context /*= nullptr*/)
{
    if (!IsValid(TextBlock))
    {
        FString Message =
            FString::Format(TEXT("Assertion failed - {0} - Text block is not valid"), {What});
        OnTestFailed(Context, Message);
        return;
    }

    if (TextBlock->GetText().IsEmpty())
    {
        FString Message = FString::Format(TEXT("Assertion failed - {0} - Text is empty"), {What});
        OnTestFailed(Context, Message);
        return;
    }
}

void UDaeTestAssertBlueprintFunctionLibrary::AssertRichTextIsSet(const FString& What,
                                                                 URichTextBlock* RichTextBlock,
                                                                 UObject* Context /*= nullptr*/)
{
    if (!IsValid(RichTextBlock))
    {
        FString Message =
            FString::Format(TEXT("Assertion failed - {0} - Rich text block is not valid"), {What});
        OnTestFailed(Context, Message);
        return;
    }

    if (RichTextBlock->GetText().IsEmpty())
    {
        FString Message =
            FString::Format(TEXT("Assertion failed - {0} - Rich text is empty"), {What});
        OnTestFailed(Context, Message);
        return;
    }
}

void UDaeTestAssertBlueprintFunctionLibrary::AssertImageIsSet(const FString& What, UImage* Image,
                                                              UObject* Context /*= nullptr*/)
{
    if (!IsValid(Image))
    {
        FString Message =
            FString::Format(TEXT("Assertion failed - {0} - Image is not valid"), {What});
        OnTestFailed(Context, Message);
        return;
    }

    if (!IsValid(Image->Brush.GetResourceObject()))
    {
        FString Message = FString::Format(TEXT("Assertion failed - {0} - Image brush has no "
                                               "resource object (e.g. texture or material)"),
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
