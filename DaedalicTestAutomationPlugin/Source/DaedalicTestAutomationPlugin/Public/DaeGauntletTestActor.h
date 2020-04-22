#pragma once

#include <CoreMinimal.h>
#include <GameFramework/Actor.h>
#include "DaeGauntletTestActor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDaeGauntletTestActorTestSuccessfulSignature,
                                            ADaeGauntletTestActor*, Test);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDaeGauntletTestActorTestFailedSignature,
                                            ADaeGauntletTestActor*, Test);

/** Single automated test to be run as part of a test suite. */
UCLASS()
class DAEDALICTESTAUTOMATIONPLUGIN_API ADaeGauntletTestActor : public AActor
{
    GENERATED_BODY()

public:
    /** Starts executing this test. */
    void RunTest();

    /** Finishes execution of this test, automatically following up with the Assert step. */
    UFUNCTION(BlueprintCallable)
    void FinishAct();

    /** Finishes the current test as failure. */
    UFUNCTION(BlueprintCallable)
    void AssertFail(const FString& What);

    /** Expects the specified value to be true. */
    UFUNCTION(BlueprintCallable)
    void AssertTrue(const FString& What, bool bValue);

    /** Expects the specified value to be false. */
    UFUNCTION(BlueprintCallable)
    void AssertFalse(const FString& What, bool bValue);

    /** Expects the specified vectors to be (nearly) equal. */
    UFUNCTION(BlueprintCallable, meta = (DisplayName = "Assert Equals (Vector)"))
    void AssertEqualsVector(const FString& What, const FVector& Actual, const FVector& Expected);

    /** Event when this test has finished successfully. */
    virtual void NotifyOnTestSuccessful();

    /** Event when this test has failed. */
    virtual void NotifyOnTestFailed(const FString& Message);

    /** Event when this test should set up. */
    virtual void NotifyOnArrange();

    /** Event when this test should execute. */
    virtual void NotifyOnAct();

    /** Event when this test should check the results. */
    virtual void NotifyOnAssert();

    /** Event when this test should set up. This is NOT a latent event. */
    UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "Arrange"))
    void ReceiveOnArrange();

    /** Event when this test should execute. This is a latent event: You need to call FinishAct when you're finished. */
    UFUNCTION(BlueprintNativeEvent, meta = (DisplayName = "Act"))
    void ReceiveOnAct();

    /** Event when this test should check the results. This is NOT a latent event. */
    UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "Assert"))
    void ReceiveOnAssert();

    /** Event when this test has finished successfully. */
    FDaeGauntletTestActorTestSuccessfulSignature OnTestSuccessful;

    /** Event when this test has failed. */
    FDaeGauntletTestActorTestFailedSignature OnTestFailed;

private:
    static const FString ErrorMessageFormat;

    /** Whether this test has finished executing (either with success or failure). */
    bool bHasResult;
};
