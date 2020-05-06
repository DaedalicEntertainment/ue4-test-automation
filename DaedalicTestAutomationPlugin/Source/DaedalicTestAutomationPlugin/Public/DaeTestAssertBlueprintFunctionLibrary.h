#pragma once

#include <CoreMinimal.h>
#include <Kismet/BlueprintFunctionLibrary.h>
#include "DaeTestAssertBlueprintFunctionLibrary.generated.h"

class UImage;
class URichTextBlock;
class UTextBlock;
class UUserWidget;

class ADaeTestTriggerBox;

/** Utility functions for asserting state in automated tests. */
UCLASS()
class DAEDALICTESTAUTOMATIONPLUGIN_API UDaeTestAssertBlueprintFunctionLibrary
    : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    /** Finishes the current test as failure. */
    UFUNCTION(BlueprintCallable, meta = (HidePin = "Context", DefaultToSelf = "Context"))
    static void AssertFail(UObject* Context, const FString& What);

    /** Expects the specified value to be true. */
    UFUNCTION(BlueprintCallable, meta = (HidePin = "Context", DefaultToSelf = "Context"))
    static void AssertTrue(UObject* Context, const FString& What, bool bValue);

    /** Expects the specified value to be false. */
    UFUNCTION(BlueprintCallable, meta = (HidePin = "Context", DefaultToSelf = "Context"))
    static void AssertFalse(UObject* Context, const FString& What, bool bValue);

    /** Expects the specified object to be valid. */
    UFUNCTION(BlueprintCallable, meta = (HidePin = "Context", DefaultToSelf = "Context"))
    static void AssertValid(UObject* Context, const FString& What, UObject* Object);

    /** Expects the specified object not to be valid. */
    UFUNCTION(BlueprintCallable, meta = (HidePin = "Context", DefaultToSelf = "Context"))
    static void AssertInvalid(UObject* Context, const FString& What, UObject* Object);

    /** Expects the specified trigger box to be triggered. */
    UFUNCTION(BlueprintCallable, meta = (HidePin = "Context", DefaultToSelf = "Context"))
    static void AssertWasTriggered(UObject* Context, ADaeTestTriggerBox* TestTriggerBox);

    /** Expects the specified trigger box not to be triggered. */
    UFUNCTION(BlueprintCallable, meta = (HidePin = "Context", DefaultToSelf = "Context"))
    static void AssertWasNotTriggered(UObject* Context, ADaeTestTriggerBox* TestTriggerBox);

    /** Expects the specified bytes to be equal. */
    UFUNCTION(BlueprintCallable, meta = (HidePin = "Context", DefaultToSelf = "Context",
                                         DisplayName = "Assert Equal (Byte)"))
    static void AssertEqualByte(UObject* Context, const FString& What, uint8 Actual,
                                uint8 Expected);

    /** Expects the specified bytes not to be equal. */
    UFUNCTION(BlueprintCallable, meta = (HidePin = "Context", DefaultToSelf = "Context",
                                         DisplayName = "Assert Not Equal (Byte)"))
    static void AssertNotEqualByte(UObject* Context, const FString& What, uint8 Actual,
                                   uint8 Unexpected);

    /** Expects the specified 32-bit integers to be equal. */
    UFUNCTION(BlueprintCallable, meta = (HidePin = "Context", DefaultToSelf = "Context",
                                         DisplayName = "Assert Equal (Integer)"))
    static void AssertEqualInt32(UObject* Context, const FString& What, int32 Actual,
                                 int32 Expected);

    /** Expects the specified 32-bit integers not to be equal. */
    UFUNCTION(BlueprintCallable, meta = (HidePin = "Context", DefaultToSelf = "Context",
                                         DisplayName = "Assert Not Equal (Integer)"))
    static void AssertNotEqualInt32(UObject* Context, const FString& What, int32 Actual,
                                    int32 Unexpected);

    /** Expects the specified 64-bit integers to be equal. */
    UFUNCTION(BlueprintCallable, meta = (HidePin = "Context", DefaultToSelf = "Context",
                                         DisplayName = "Assert Equal (Integer64)"))
    static void AssertEqualInt64(UObject* Context, const FString& What, int64 Actual,
                                 int64 Expected);

    /** Expects the specified 64-bit integers not to be equal. */
    UFUNCTION(BlueprintCallable, meta = (HidePin = "Context", DefaultToSelf = "Context",
                                         DisplayName = "Assert Not Equal (Integer64)"))
    static void AssertNotEqualInt64(UObject* Context, const FString& What, int64 Actual,
                                    int64 Unexpected);

    /** Expects the specified floats to be (nearly) equal. */
    UFUNCTION(BlueprintCallable, meta = (HidePin = "Context", DefaultToSelf = "Context",
                                         DisplayName = "Assert Equal (Float)"))
    static void AssertEqualFloat(UObject* Context, const FString& What, float Actual,
                                 float Expected);

    /** Expects the specified floats not to be equal. */
    UFUNCTION(BlueprintCallable, meta = (HidePin = "Context", DefaultToSelf = "Context",
                                         DisplayName = "Assert Not Equal (Float)"))
    static void AssertNotEqualFloat(UObject* Context, const FString& What, float Actual,
                                    float Unexpected);

    /** Expects the specified names to be equal. */
    UFUNCTION(BlueprintCallable, meta = (HidePin = "Context", DefaultToSelf = "Context",
                                         DisplayName = "Assert Equal (Name)"))
    static void AssertEqualName(UObject* Context, const FString& What, const FName& Actual,
                                const FName& Expected);

    /** Expects the specified names not to be equal. */
    UFUNCTION(BlueprintCallable, meta = (HidePin = "Context", DefaultToSelf = "Context",
                                         DisplayName = "Assert Not Equal (Name)"))
    static void AssertNotEqualName(UObject* Context, const FString& What, const FName& Actual,
                                   const FName& Unexpected);

    /** Expects the specified strings to be equal. */
    UFUNCTION(BlueprintCallable, meta = (HidePin = "Context", DefaultToSelf = "Context",
                                         DisplayName = "Assert Equal (String)"))
    static void AssertEqualString(UObject* Context, const FString& What, const FString& Actual,
                                  const FString& Expected);

    /** Expects the specified strings not to be equal. */
    UFUNCTION(BlueprintCallable, meta = (HidePin = "Context", DefaultToSelf = "Context",
                                         DisplayName = "Assert Not Equal (String)"))
    static void AssertNotEqualString(UObject* Context, const FString& What, const FString& Actual,
                                     const FString& Unexpected);

    /** Expects the specified texts to be equal. */
    UFUNCTION(BlueprintCallable, meta = (HidePin = "Context", DefaultToSelf = "Context",
                                         DisplayName = "Assert Equal (Text)"))
    static void AssertEqualText(UObject* Context, const FString& What, const FText& Actual,
                                const FText& Expected);

    /** Expects the specified texts not to be equal. */
    UFUNCTION(BlueprintCallable, meta = (HidePin = "Context", DefaultToSelf = "Context",
                                         DisplayName = "Assert Not Equal (Text)"))
    static void AssertNotEqualText(UObject* Context, const FString& What, const FText& Actual,
                                   const FText& Unexpected);

    /** Expects the specified vectors to be (nearly) equal. */
    UFUNCTION(BlueprintCallable, meta = (HidePin = "Context", DefaultToSelf = "Context",
                                         DisplayName = "Assert Equal (Vector)"))
    static void AssertEqualVector(UObject* Context, const FString& What, const FVector& Actual,
                                  const FVector& Expected);

    /** Expects the specified vectors not to be equal. */
    UFUNCTION(BlueprintCallable, meta = (HidePin = "Context", DefaultToSelf = "Context",
                                         DisplayName = "Assert Not Equal (Vector)"))
    static void AssertNotEqualVector(UObject* Context, const FString& What, const FVector& Actual,
                                     const FVector& Unexpected);

    /** Expects the specified rotators to be (nearly) equal. */
    UFUNCTION(BlueprintCallable, meta = (HidePin = "Context", DefaultToSelf = "Context",
                                         DisplayName = "Assert Equal (Rotator)"))
    static void AssertEqualRotator(UObject* Context, const FString& What, const FRotator& Actual,
                                   const FRotator& Expected);

    /** Expects the specified rotators not to be equal. */
    UFUNCTION(BlueprintCallable, meta = (HidePin = "Context", DefaultToSelf = "Context",
                                         DisplayName = "Assert Not Equal (Rotator)"))
    static void AssertNotEqualRotator(UObject* Context, const FString& What, const FRotator& Actual,
                                      const FRotator& Unexpected);

    /** Expects the specified transforms to be (nearly) equal. */
    UFUNCTION(BlueprintCallable, meta = (HidePin = "Context", DefaultToSelf = "Context",
                                         DisplayName = "Assert Equal (Transform)"))
    static void AssertEqualTransform(UObject* Context, const FString& What,
                                     const FTransform& Actual, const FTransform& Expected);

    /** Expects the specified transforms not to be equal. */
    UFUNCTION(BlueprintCallable, meta = (HidePin = "Context", DefaultToSelf = "Context",
                                         DisplayName = "Assert Not Equal (Transform)"))
    static void AssertNotEqualTransform(UObject* Context, const FString& What,
                                        const FTransform& Actual, const FTransform& Unexpected);

    /** Expects Value to be between MinInclusive and MaxInclusive. */
    UFUNCTION(BlueprintCallable, meta = (HidePin = "Context", DefaultToSelf = "Context",
                                         DisplayName = "Assert In Range (Byte)"))
    static void AssertInRangeByte(UObject* Context, const FString& What, uint8 Value,
                                  uint8 MinInclusive, uint8 MaxInclusive);

    /** Expects Value not to be between MinInclusive and MaxInclusive. */
    UFUNCTION(BlueprintCallable, meta = (HidePin = "Context", DefaultToSelf = "Context",
                                         DisplayName = "Assert Not In Range (Byte)"))
    static void AssertNotInRangeByte(UObject* Context, const FString& What, uint8 Value,
                                     uint8 MinInclusive, uint8 MaxInclusive);

    /** Expects Value to be between MinInclusive and MaxInclusive. */
    UFUNCTION(BlueprintCallable, meta = (HidePin = "Context", DefaultToSelf = "Context",
                                         DisplayName = "Assert In Range (Integer)"))
    static void AssertInRangeInt32(UObject* Context, const FString& What, int32 Value,
                                   int32 MinInclusive, int32 MaxInclusive);

    /** Expects Value not to be between MinInclusive and MaxInclusive. */
    UFUNCTION(BlueprintCallable, meta = (HidePin = "Context", DefaultToSelf = "Context",
                                         DisplayName = "Assert Not In Range (Integer)"))
    static void AssertNotInRangeInt32(UObject* Context, const FString& What, int32 Value,
                                      int32 MinInclusive, int32 MaxInclusive);

    /** Expects Value to be between MinInclusive and MaxInclusive. */
    UFUNCTION(BlueprintCallable, meta = (HidePin = "Context", DefaultToSelf = "Context",
                                         DisplayName = "Assert In Range (Integer64)"))
    static void AssertInRangeInt64(UObject* Context, const FString& What, int64 Value,
                                   int64 MinInclusive, int64 MaxInclusive);

    /** Expects Value not to be between MinInclusive and MaxInclusive. */
    UFUNCTION(BlueprintCallable, meta = (HidePin = "Context", DefaultToSelf = "Context",
                                         DisplayName = "Assert Not In Range (Integer64)"))
    static void AssertNotInRangeInt64(UObject* Context, const FString& What, int64 Value,
                                      int64 MinInclusive, int64 MaxInclusive);

    /** Expects Value to be between MinInclusive and MaxInclusive. */
    UFUNCTION(BlueprintCallable, meta = (HidePin = "Context", DefaultToSelf = "Context",
                                         DisplayName = "Assert In Range (Float)"))
    static void AssertInRangeFloat(UObject* Context, const FString& What, float Value,
                                   float MinInclusive, float MaxInclusive);

    /** Expects Value not to be between MinInclusive and MaxInclusive. */
    UFUNCTION(BlueprintCallable, meta = (HidePin = "Context", DefaultToSelf = "Context",
                                         DisplayName = "Assert Not In Range (Float)"))
    static void AssertNotInRangeFloat(UObject* Context, const FString& What, float Value,
                                      float MinInclusive, float MaxInclusive);

    /** Expects the specified widget to be valid and visible. */
    UFUNCTION(BlueprintCallable, meta = (HidePin = "Context", DefaultToSelf = "Context"))
    static void AssertWidgetIsVisible(UObject* Context, const FString& What, UUserWidget* Widget);

    /** Expects the specified text not to be empty. */
    UFUNCTION(BlueprintCallable, meta = (HidePin = "Context", DefaultToSelf = "Context"))
    static void AssertTextIsSet(UObject* Context, const FString& What, UTextBlock* TextBlock);

    /** Expects the specified rich text not to be empty. */
    UFUNCTION(BlueprintCallable, meta = (HidePin = "Context", DefaultToSelf = "Context"))
    static void AssertRichTextIsSet(UObject* Context, const FString& What,
                                    URichTextBlock* RichTextBlock);

    /** Expects the specified image to be set up to use a texture or material. */
    UFUNCTION(BlueprintCallable, meta = (HidePin = "Context", DefaultToSelf = "Context"))
    static void AssertImageIsSet(UObject* Context, const FString& What, UImage* Image);

private:
    static const FString ErrorMessageFormatEqual;
    static const FString ErrorMessageFormatNotEqual;
    static const FString ErrorMessageFormatInRange;
    static const FString ErrorMessageFormatNotInRange;

    static void OnTestFailed(UObject* Context, const FString& Message);

    template<typename T>
    static void AssertEqual(UObject* Context, const FString& What, T Actual, T Expected)
    {
        if (Actual != Expected)
        {
            FString Message = FString::Format(*ErrorMessageFormatEqual, {What, Expected, Actual});
            OnTestFailed(Context, Message);
        }
    }

    template<typename T>
    static void AssertNotEqual(UObject* Context, const FString& What, T Actual, T Unexpected)
    {
        if (Actual == Unexpected)
        {
            FString Message = FString::Format(*ErrorMessageFormatNotEqual, {What, Unexpected});
            OnTestFailed(Context, Message);
        }
    }
};
