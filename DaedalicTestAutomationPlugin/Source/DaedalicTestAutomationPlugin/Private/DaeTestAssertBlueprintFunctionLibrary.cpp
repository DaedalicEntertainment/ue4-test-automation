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

void UDaeTestAssertBlueprintFunctionLibrary::AssertFail(UObject* Context, const FString& What)
{
    OnTestFailed(Context, What);
}

void UDaeTestAssertBlueprintFunctionLibrary::AssertTrue(UObject* Context, const FString& What,
                                                        bool bValue)
{
    if (!bValue)
    {
        FString Message =
            FString::Format(*ErrorMessageFormatEqual, {What, TEXT("True"), TEXT("False")});
        OnTestFailed(Context, Message);
    }
}

void UDaeTestAssertBlueprintFunctionLibrary::AssertFalse(UObject* Context, const FString& What,
                                                         bool bValue)
{
    if (bValue)
    {
        FString Message =
            FString::Format(*ErrorMessageFormatEqual, {What, TEXT("False"), TEXT("True")});
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

void UDaeTestAssertBlueprintFunctionLibrary::AssertWasNotTriggered(
    UObject* Context, ADaeTestTriggerBox* TestTriggerBox)
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

void UDaeTestAssertBlueprintFunctionLibrary::AssertEqualByte(UObject* Context, const FString& What,
                                                             uint8 Actual, uint8 Expected)
{
    AssertEqual(Context, What, Actual, Expected);
}

void UDaeTestAssertBlueprintFunctionLibrary::AssertNotEqualByte(UObject* Context,
                                                                const FString& What, uint8 Actual,
                                                                uint8 Unexpected)
{
    AssertNotEqual(Context, What, Actual, Unexpected);
}

void UDaeTestAssertBlueprintFunctionLibrary::AssertEqualInt32(UObject* Context, const FString& What,
                                                              int32 Actual, int32 Expected)
{
    AssertEqual(Context, What, Actual, Expected);
}

void UDaeTestAssertBlueprintFunctionLibrary::AssertNotEqualInt32(UObject* Context,
                                                                 const FString& What, int32 Actual,
                                                                 int32 Unexpected)
{
    AssertNotEqual(Context, What, Actual, Unexpected);
}

void UDaeTestAssertBlueprintFunctionLibrary::AssertEqualInt64(UObject* Context, const FString& What,
                                                              int64 Actual, int64 Expected)
{
    AssertEqual(Context, What, Actual, Expected);
}

void UDaeTestAssertBlueprintFunctionLibrary::AssertNotEqualInt64(UObject* Context,
                                                                 const FString& What, int64 Actual,
                                                                 int64 Unexpected)
{
    AssertNotEqual(Context, What, Actual, Unexpected);
}

void UDaeTestAssertBlueprintFunctionLibrary::AssertEqualFloat(UObject* Context, const FString& What,
                                                              float Actual, float Expected)
{
    if (!FMath::IsNearlyEqual(Actual, Expected))
    {
        FString Message = FString::Format(*ErrorMessageFormatEqual, {What, Expected, Actual});
        OnTestFailed(Context, Message);
    }
}

void UDaeTestAssertBlueprintFunctionLibrary::AssertNotEqualFloat(UObject* Context,
                                                                 const FString& What, float Actual,
                                                                 float Unexpected)
{
    if (FMath::IsNearlyEqual(Actual, Unexpected))
    {
        FString Message = FString::Format(*ErrorMessageFormatNotEqual, {What, Unexpected});
        OnTestFailed(Context, Message);
    }
}

void UDaeTestAssertBlueprintFunctionLibrary::AssertEqualName(UObject* Context, const FString& What,
                                                             const FName& Actual,
                                                             const FName& Expected)
{
    if (!Actual.IsEqual(Expected))
    {
        FString Message = FString::Format(*ErrorMessageFormatEqual,
                                          {What, Expected.ToString(), Actual.ToString()});
        OnTestFailed(Context, Message);
    }
}

void UDaeTestAssertBlueprintFunctionLibrary::AssertNotEqualName(UObject* Context,
                                                                const FString& What,
                                                                const FName& Actual,
                                                                const FName& Unexpected)
{
    if (Actual.IsEqual(Unexpected))
    {
        FString Message =
            FString::Format(*ErrorMessageFormatNotEqual, {What, Unexpected.ToString()});
        OnTestFailed(Context, Message);
    }
}

void UDaeTestAssertBlueprintFunctionLibrary::AssertEqualString(UObject* Context,
                                                               const FString& What,
                                                               const FString& Actual,
                                                               const FString& Expected)
{
    if (!Actual.Equals(Expected))
    {
        FString Message = FString::Format(*ErrorMessageFormatEqual, {What, Expected, Actual});
        OnTestFailed(Context, Message);
    }
}

void UDaeTestAssertBlueprintFunctionLibrary::AssertNotEqualString(UObject* Context,
                                                                  const FString& What,
                                                                  const FString& Actual,
                                                                  const FString& Unexpected)
{
    if (Actual.Equals(Unexpected))
    {
        FString Message = FString::Format(*ErrorMessageFormatNotEqual, {What, Unexpected});
        OnTestFailed(Context, Message);
    }
}

void UDaeTestAssertBlueprintFunctionLibrary::AssertEqualText(UObject* Context, const FString& What,
                                                             const FText& Actual,
                                                             const FText& Expected)
{
    if (!Actual.EqualTo(Expected))
    {
        FString Message = FString::Format(*ErrorMessageFormatEqual,
                                          {What, Expected.ToString(), Actual.ToString()});
        OnTestFailed(Context, Message);
    }
}

void UDaeTestAssertBlueprintFunctionLibrary::AssertNotEqualText(UObject* Context,
                                                                const FString& What,
                                                                const FText& Actual,
                                                                const FText& Unexpected)
{
    if (Actual.EqualTo(Unexpected))
    {
        FString Message =
            FString::Format(*ErrorMessageFormatNotEqual, {What, Unexpected.ToString()});
        OnTestFailed(Context, Message);
    }
}

void UDaeTestAssertBlueprintFunctionLibrary::AssertEqualVector(UObject* Context,
                                                               const FString& What,
                                                               const FVector& Actual,
                                                               const FVector& Expected)
{
    if (!Actual.Equals(Expected))
    {
        FString Message = FString::Format(*ErrorMessageFormatEqual,
                                          {What, Expected.ToString(), Actual.ToString()});
        OnTestFailed(Context, Message);
    }
}

void UDaeTestAssertBlueprintFunctionLibrary::AssertNotEqualVector(UObject* Context,
                                                                  const FString& What,
                                                                  const FVector& Actual,
                                                                  const FVector& Unexpected)
{
    if (Actual.Equals(Unexpected))
    {
        FString Message =
            FString::Format(*ErrorMessageFormatNotEqual, {What, Unexpected.ToString()});
        OnTestFailed(Context, Message);
    }
}

void UDaeTestAssertBlueprintFunctionLibrary::AssertEqualRotator(UObject* Context,
                                                                const FString& What,
                                                                const FRotator& Actual,
                                                                const FRotator& Expected)
{
    if (!Actual.Equals(Expected))
    {
        FString Message = FString::Format(*ErrorMessageFormatEqual,
                                          {What, Expected.ToString(), Actual.ToString()});
        OnTestFailed(Context, Message);
    }
}

void UDaeTestAssertBlueprintFunctionLibrary::AssertNotEqualRotator(UObject* Context,
                                                                   const FString& What,
                                                                   const FRotator& Actual,
                                                                   const FRotator& Unexpected)
{
    if (Actual.Equals(Unexpected))
    {
        FString Message =
            FString::Format(*ErrorMessageFormatNotEqual, {What, Unexpected.ToString()});
        OnTestFailed(Context, Message);
    }
}

void UDaeTestAssertBlueprintFunctionLibrary::AssertEqualTransform(UObject* Context,
                                                                  const FString& What,
                                                                  const FTransform& Actual,
                                                                  const FTransform& Expected)
{
    if (!Actual.Equals(Expected))
    {
        FString Message = FString::Format(*ErrorMessageFormatEqual,
                                          {What, Expected.ToString(), Actual.ToString()});
        OnTestFailed(Context, Message);
    }
}

void UDaeTestAssertBlueprintFunctionLibrary::AssertNotEqualTransform(UObject* Context,
                                                                     const FString& What,
                                                                     const FTransform& Actual,
                                                                     const FTransform& Unexpected)
{
    if (Actual.Equals(Unexpected))
    {
        FString Message =
            FString::Format(*ErrorMessageFormatNotEqual, {What, Unexpected.ToString()});
        OnTestFailed(Context, Message);
    }
}

void UDaeTestAssertBlueprintFunctionLibrary::AssertInRangeByte(UObject* Context,
                                                               const FString& What, uint8 Value,
                                                               uint8 MinInclusive,
                                                               uint8 MaxInclusive)
{
    AssertInRangeInt32(Context, What, Value, MinInclusive, MaxInclusive);
}

void UDaeTestAssertBlueprintFunctionLibrary::AssertNotInRangeByte(UObject* Context,
                                                                  const FString& What, uint8 Value,
                                                                  uint8 MinInclusive,
                                                                  uint8 MaxInclusive)
{
    AssertNotInRangeInt32(Context, What, Value, MinInclusive, MaxInclusive);
}

void UDaeTestAssertBlueprintFunctionLibrary::AssertInRangeInt32(UObject* Context,
                                                                const FString& What, int32 Value,
                                                                int32 MinInclusive,
                                                                int32 MaxInclusive)
{
    if (!UKismetMathLibrary::InRange_IntInt(Value, MinInclusive, MaxInclusive))
    {
        FString Message =
            FString::Format(*ErrorMessageFormatInRange, {What, MinInclusive, MaxInclusive, Value});
        OnTestFailed(Context, Message);
    }
}

void UDaeTestAssertBlueprintFunctionLibrary::AssertNotInRangeInt32(UObject* Context,
                                                                   const FString& What, int32 Value,
                                                                   int32 MinInclusive,
                                                                   int32 MaxInclusive)
{
    if (UKismetMathLibrary::InRange_IntInt(Value, MinInclusive, MaxInclusive))
    {
        FString Message = FString::Format(*ErrorMessageFormatNotInRange,
                                          {What, MinInclusive, MaxInclusive, Value});
        OnTestFailed(Context, Message);
    }
}

void UDaeTestAssertBlueprintFunctionLibrary::AssertInRangeInt64(UObject* Context,
                                                                const FString& What, int64 Value,
                                                                int64 MinInclusive,
                                                                int64 MaxInclusive)
{
    if (!UKismetMathLibrary::InRange_Int64Int64(Value, MinInclusive, MaxInclusive))
    {
        FString Message =
            FString::Format(*ErrorMessageFormatInRange, {What, MinInclusive, MaxInclusive, Value});
        OnTestFailed(Context, Message);
    }
}

void UDaeTestAssertBlueprintFunctionLibrary::AssertNotInRangeInt64(UObject* Context,
                                                                   const FString& What, int64 Value,
                                                                   int64 MinInclusive,
                                                                   int64 MaxInclusive)
{
    if (UKismetMathLibrary::InRange_Int64Int64(Value, MinInclusive, MaxInclusive))
    {
        FString Message = FString::Format(*ErrorMessageFormatNotInRange,
                                          {What, MinInclusive, MaxInclusive, Value});
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
        FString Message =
            FString::Format(*ErrorMessageFormatInRange, {What, MinInclusive, MaxInclusive, Value});
        OnTestFailed(Context, Message);
    }
}

void UDaeTestAssertBlueprintFunctionLibrary::AssertNotInRangeFloat(UObject* Context,
                                                                   const FString& What, float Value,
                                                                   float MinInclusive,
                                                                   float MaxInclusive)
{
    if (UKismetMathLibrary::InRange_FloatFloat(Value, MinInclusive, MaxInclusive))
    {
        FString Message = FString::Format(*ErrorMessageFormatNotInRange,
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

void UDaeTestAssertBlueprintFunctionLibrary::AssertTextIsSet(UObject* Context, const FString& What,
                                                             UTextBlock* TextBlock)
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

void UDaeTestAssertBlueprintFunctionLibrary::AssertRichTextIsSet(UObject* Context,
                                                                 const FString& What,
                                                                 URichTextBlock* RichTextBlock)
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

void UDaeTestAssertBlueprintFunctionLibrary::AssertImageIsSet(UObject* Context, const FString& What,
                                                              UImage* Image)
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
