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
    static void AssertFail(const FString& What, UObject* Context = nullptr);

    /** Expects the specified value to be true. */
    UFUNCTION(BlueprintCallable, meta = (HidePin = "Context", DefaultToSelf = "Context"))
    static void AssertTrue(const FString& What, bool bValue, UObject* Context = nullptr);

    /** Expects the specified value to be false. */
    UFUNCTION(BlueprintCallable, meta = (HidePin = "Context", DefaultToSelf = "Context"))
    static void AssertFalse(const FString& What, bool bValue, UObject* Context = nullptr);

    /** Expects the specified object to be valid. */
    UFUNCTION(BlueprintCallable, meta = (HidePin = "Context", DefaultToSelf = "Context"))
    static void AssertValid(const FString& What, UObject* Object, UObject* Context = nullptr);

    /** Expects the specified object not to be valid. */
    UFUNCTION(BlueprintCallable, meta = (HidePin = "Context", DefaultToSelf = "Context"))
    static void AssertInvalid(const FString& What, UObject* Object, UObject* Context = nullptr);

    /** Expects the specified trigger box to be triggered. */
    UFUNCTION(BlueprintCallable, meta = (HidePin = "Context", DefaultToSelf = "Context"))
    static void AssertWasTriggered(ADaeTestTriggerBox* TestTriggerBox, UObject* Context = nullptr);

    /** Expects the specified trigger box not to be triggered. */
    UFUNCTION(BlueprintCallable, meta = (HidePin = "Context", DefaultToSelf = "Context"))
    static void AssertWasNotTriggered(ADaeTestTriggerBox* TestTriggerBox,
                                      UObject* Context = nullptr);

    /** Expects the specified bytes to be equal. */
    UFUNCTION(BlueprintCallable, meta = (HidePin = "Context", DefaultToSelf = "Context",
                                         DisplayName = "Assert Equal (Byte)"))
    static void AssertEqualByte(const FString& What, uint8 Actual, uint8 Expected,
                                UObject* Context = nullptr);

    /** Expects the specified bytes not to be equal. */
    UFUNCTION(BlueprintCallable, meta = (HidePin = "Context", DefaultToSelf = "Context",
                                         DisplayName = "Assert Not Equal (Byte)"))
    static void AssertNotEqualByte(const FString& What, uint8 Actual, uint8 Unexpected,
                                   UObject* Context = nullptr);

    /** Expects the specified 32-bit integers to be equal. */
    UFUNCTION(BlueprintCallable, meta = (HidePin = "Context", DefaultToSelf = "Context",
                                         DisplayName = "Assert Equal (Integer)"))
    static void AssertEqualInt32(const FString& What, int32 Actual, int32 Expected,
                                 UObject* Context = nullptr);

    /** Expects the specified 32-bit integers not to be equal. */
    UFUNCTION(BlueprintCallable, meta = (HidePin = "Context", DefaultToSelf = "Context",
                                         DisplayName = "Assert Not Equal (Integer)"))
    static void AssertNotEqualInt32(const FString& What, int32 Actual, int32 Unexpected,
                                    UObject* Context = nullptr);

    /** Expects the specified 64-bit integers to be equal. */
    UFUNCTION(BlueprintCallable, meta = (HidePin = "Context", DefaultToSelf = "Context",
                                         DisplayName = "Assert Equal (Integer64)"))
    static void AssertEqualInt64(const FString& What, int64 Actual, int64 Expected,
                                 UObject* Context = nullptr);

    /** Expects the specified 64-bit integers not to be equal. */
    UFUNCTION(BlueprintCallable, meta = (HidePin = "Context", DefaultToSelf = "Context",
                                         DisplayName = "Assert Not Equal (Integer64)"))
    static void AssertNotEqualInt64(const FString& What, int64 Actual, int64 Unexpected,
                                    UObject* Context = nullptr);

    /** Expects the specified floats to be (nearly) equal. */
    UFUNCTION(BlueprintCallable, meta = (HidePin = "Context", DefaultToSelf = "Context",
                                         DisplayName = "Assert Equal (Float)"))
    static void AssertEqualFloat(const FString& What, float Actual, float Expected,
                                 UObject* Context = nullptr);

    /** Expects the specified floats not to be equal. */
    UFUNCTION(BlueprintCallable, meta = (HidePin = "Context", DefaultToSelf = "Context",
                                         DisplayName = "Assert Not Equal (Float)"))
    static void AssertNotEqualFloat(const FString& What, float Actual, float Unexpected,
                                    UObject* Context = nullptr);

    /** Expects the specified names to be equal. */
    UFUNCTION(BlueprintCallable, meta = (HidePin = "Context", DefaultToSelf = "Context",
                                         DisplayName = "Assert Equal (Name)"))
    static void AssertEqualName(const FString& What, const FName& Actual, const FName& Expected,
                                UObject* Context = nullptr);

    /** Expects the specified names not to be equal. */
    UFUNCTION(BlueprintCallable, meta = (HidePin = "Context", DefaultToSelf = "Context",
                                         DisplayName = "Assert Not Equal (Name)"))
    static void AssertNotEqualName(const FString& What, const FName& Actual,
                                   const FName& Unexpected, UObject* Context = nullptr);

    /** Expects the specified strings to be equal. */
    UFUNCTION(BlueprintCallable, meta = (HidePin = "Context", DefaultToSelf = "Context",
                                         DisplayName = "Assert Equal (String)"))
    static void AssertEqualString(const FString& What, const FString& Actual,
                                  const FString& Expected, UObject* Context = nullptr);

    /** Expects the specified strings not to be equal. */
    UFUNCTION(BlueprintCallable, meta = (HidePin = "Context", DefaultToSelf = "Context",
                                         DisplayName = "Assert Not Equal (String)"))
    static void AssertNotEqualString(const FString& What, const FString& Actual,
                                     const FString& Unexpected, UObject* Context = nullptr);

    /** Expects the specified texts to be equal. */
    UFUNCTION(BlueprintCallable, meta = (HidePin = "Context", DefaultToSelf = "Context",
                                         DisplayName = "Assert Equal (Text)"))
    static void AssertEqualText(const FString& What, const FText& Actual, const FText& Expected,
                                UObject* Context = nullptr);

    /** Expects the specified texts not to be equal. */
    UFUNCTION(BlueprintCallable, meta = (HidePin = "Context", DefaultToSelf = "Context",
                                         DisplayName = "Assert Not Equal (Text)"))
    static void AssertNotEqualText(const FString& What, const FText& Actual,
                                   const FText& Unexpected, UObject* Context = nullptr);

    /** Expects the specified vectors to be (nearly) equal. */
    UFUNCTION(BlueprintCallable, meta = (HidePin = "Context", DefaultToSelf = "Context",
                                         DisplayName = "Assert Equal (Vector)"))
    static void AssertEqualVector(const FString& What, const FVector& Actual,
                                  const FVector& Expected, UObject* Context = nullptr);

    /** Expects the specified vectors not to be equal. */
    UFUNCTION(BlueprintCallable, meta = (HidePin = "Context", DefaultToSelf = "Context",
                                         DisplayName = "Assert Not Equal (Vector)"))
    static void AssertNotEqualVector(const FString& What, const FVector& Actual,
                                     const FVector& Unexpected, UObject* Context = nullptr);

    /** Expects the specified rotators to be (nearly) equal. */
    UFUNCTION(BlueprintCallable, meta = (HidePin = "Context", DefaultToSelf = "Context",
                                         DisplayName = "Assert Equal (Rotator)"))
    static void AssertEqualRotator(const FString& What, const FRotator& Actual,
                                   const FRotator& Expected, UObject* Context = nullptr);

    /** Expects the specified rotators not to be equal. */
    UFUNCTION(BlueprintCallable, meta = (HidePin = "Context", DefaultToSelf = "Context",
                                         DisplayName = "Assert Not Equal (Rotator)"))
    static void AssertNotEqualRotator(const FString& What, const FRotator& Actual,
                                      const FRotator& Unexpected, UObject* Context = nullptr);

    /** Expects the specified transforms to be (nearly) equal. */
    UFUNCTION(BlueprintCallable, meta = (HidePin = "Context", DefaultToSelf = "Context",
                                         DisplayName = "Assert Equal (Transform)"))
    static void AssertEqualTransform(const FString& What, const FTransform& Actual,
                                     const FTransform& Expected, UObject* Context = nullptr);

    /** Expects the specified transforms not to be equal. */
    UFUNCTION(BlueprintCallable, meta = (HidePin = "Context", DefaultToSelf = "Context",
                                         DisplayName = "Assert Not Equal (Transform)"))
    static void AssertNotEqualTransform(const FString& What, const FTransform& Actual,
                                        const FTransform& Unexpected, UObject* Context = nullptr);

    /** Expects Value to be between MinInclusive and MaxInclusive. */
    UFUNCTION(BlueprintCallable, meta = (HidePin = "Context", DefaultToSelf = "Context",
                                         DisplayName = "Assert In Range (Byte)"))
    static void AssertInRangeByte(const FString& What, uint8 Value, uint8 MinInclusive,
                                  uint8 MaxInclusive, UObject* Context = nullptr);

    /** Expects Value not to be between MinInclusive and MaxInclusive. */
    UFUNCTION(BlueprintCallable, meta = (HidePin = "Context", DefaultToSelf = "Context",
                                         DisplayName = "Assert Not In Range (Byte)"))
    static void AssertNotInRangeByte(const FString& What, uint8 Value, uint8 MinInclusive,
                                     uint8 MaxInclusive, UObject* Context = nullptr);

    /** Expects Value to be between MinInclusive and MaxInclusive. */
    UFUNCTION(BlueprintCallable, meta = (HidePin = "Context", DefaultToSelf = "Context",
                                         DisplayName = "Assert In Range (Integer)"))
    static void AssertInRangeInt32(const FString& What, int32 Value, int32 MinInclusive,
                                   int32 MaxInclusive, UObject* Context = nullptr);

    /** Expects Value not to be between MinInclusive and MaxInclusive. */
    UFUNCTION(BlueprintCallable, meta = (HidePin = "Context", DefaultToSelf = "Context",
                                         DisplayName = "Assert Not In Range (Integer)"))
    static void AssertNotInRangeInt32(const FString& What, int32 Value, int32 MinInclusive,
                                      int32 MaxInclusive, UObject* Context = nullptr);

    /** Expects Value to be between MinInclusive and MaxInclusive. */
    UFUNCTION(BlueprintCallable, meta = (HidePin = "Context", DefaultToSelf = "Context",
                                         DisplayName = "Assert In Range (Integer64)"))
    static void AssertInRangeInt64(const FString& What, int64 Value, int64 MinInclusive,
                                   int64 MaxInclusive, UObject* Context = nullptr);

    /** Expects Value not to be between MinInclusive and MaxInclusive. */
    UFUNCTION(BlueprintCallable, meta = (HidePin = "Context", DefaultToSelf = "Context",
                                         DisplayName = "Assert Not In Range (Integer64)"))
    static void AssertNotInRangeInt64(const FString& What, int64 Value, int64 MinInclusive,
                                      int64 MaxInclusive, UObject* Context = nullptr);

    /** Expects Value to be between MinInclusive and MaxInclusive. */
    UFUNCTION(BlueprintCallable, meta = (HidePin = "Context", DefaultToSelf = "Context",
                                         DisplayName = "Assert In Range (Float)"))
    static void AssertInRangeFloat(const FString& What, float Value, float MinInclusive,
                                   float MaxInclusive, UObject* Context = nullptr);

    /** Expects Value not to be between MinInclusive and MaxInclusive. */
    UFUNCTION(BlueprintCallable, meta = (HidePin = "Context", DefaultToSelf = "Context",
                                         DisplayName = "Assert Not In Range (Float)"))
    static void AssertNotInRangeFloat(const FString& What, float Value, float MinInclusive,
                                      float MaxInclusive, UObject* Context = nullptr);

    /** Expects the specified widget to be valid and visible. */
    UFUNCTION(BlueprintCallable, meta = (HidePin = "Context", DefaultToSelf = "Context"))
    static void AssertWidgetIsVisible(const FString& What, UUserWidget* Widget,
                                      UObject* Context = nullptr);

    /** Expects the specified text not to be empty. */
    UFUNCTION(BlueprintCallable, meta = (HidePin = "Context", DefaultToSelf = "Context"))
    static void AssertTextIsSet(const FString& What, UTextBlock* TextBlock,
                                UObject* Context = nullptr);

    /** Expects the specified rich text not to be empty. */
    UFUNCTION(BlueprintCallable, meta = (HidePin = "Context", DefaultToSelf = "Context"))
    static void AssertRichTextIsSet(const FString& What, URichTextBlock* RichTextBlock,
                                    UObject* Context = nullptr);

    /** Expects the specified image to be set up to use a texture or material. */
    UFUNCTION(BlueprintCallable, meta = (HidePin = "Context", DefaultToSelf = "Context"))
    static void AssertImageIsSet(const FString& What, UImage* Image, UObject* Context = nullptr);

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
