#pragma once

#include <CoreMinimal.h>
#include <Kismet/BlueprintFunctionLibrary.h>
#include "DaeTestAssertBlueprintFunctionLibrary.generated.h"

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

private:
    static const FString ErrorMessageFormat;

    static void OnTestFailed(UObject* Context, const FString& Message);
};
