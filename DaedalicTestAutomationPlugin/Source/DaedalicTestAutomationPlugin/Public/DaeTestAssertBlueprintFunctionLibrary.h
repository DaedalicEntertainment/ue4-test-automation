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

    /** Expects the specified vectors to be (nearly) equal. */
    UFUNCTION(BlueprintCallable, meta = (HidePin = "Context", DefaultToSelf = "Context",
                                         DisplayName = "Assert Equals (Vector)"))
    static void AssertEqualsVector(UObject* Context, const FString& What, const FVector& Actual,
                                   const FVector& Expected);

    /** Expects Value to be between MinInclusive and MaxInclusive. */
    UFUNCTION(BlueprintCallable, meta = (HidePin = "Context", DefaultToSelf = "Context",
                                         DisplayName = "Assert In Range (Float)"))
    static void AssertInRangeFloat(UObject* Context, const FString& What, float Value,
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
    static const FString ErrorMessageFormat;

    static void OnTestFailed(UObject* Context, const FString& Message);
};
