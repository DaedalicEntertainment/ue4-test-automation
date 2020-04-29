#pragma once

#include <CoreMinimal.h>
#include <GameFramework/Actor.h>
#include "DaeTestActor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDaeTestActorTestSuccessfulSignature, ADaeTestActor*,
                                            Test);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FDaeTestActorTestFailedSignature, ADaeTestActor*, Test,
                                             const FString&, FailureMessage);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FDaeTestActorTestSkippedSignature, ADaeTestActor*,
                                             Test, const FString&, SkipReason);

class ADaeTestTriggerBox;

/** Single automated test to be run as part of a test suite. */
UCLASS()
class DAEDALICTESTAUTOMATIONPLUGIN_API ADaeTestActor : public AActor
{
    GENERATED_BODY()

public:
    ADaeTestActor(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

    /** Starts executing this test. */
    void RunTest();

    /** Finishes execution of this test, automatically following up with the Assert step. */
    UFUNCTION(BlueprintCallable)
    void FinishAct();

    /** Applies the input action with the specified name once. */
    UFUNCTION(BlueprintCallable)
    void ApplyInputAction(const FName& ActionName);

    /** Applies the input axis with the specified name. Pass AxisValue 0.0f to reset the input axis. */
    UFUNCTION(BlueprintCallable)
    void ApplyInputAxis(const FName& AxisName, float AxisValue = 1.0f);

    /** Finishes the current test as failure. */
    UFUNCTION(BlueprintCallable)
    void AssertFail(const FString& What);

    /** Expects the specified value to be true. */
    UFUNCTION(BlueprintCallable)
    void AssertTrue(const FString& What, bool bValue);

    /** Expects the specified value to be false. */
    UFUNCTION(BlueprintCallable)
    void AssertFalse(const FString& What, bool bValue);

    /** Expects the specified trigger box to be triggered. */
    UFUNCTION(BlueprintCallable)
    void AssertWasTriggered(ADaeTestTriggerBox* TestTriggerBox);

    /** Expects the specified vectors to be (nearly) equal. */
    UFUNCTION(BlueprintCallable, meta = (DisplayName = "Assert Equals (Vector)"))
    void AssertEqualsVector(const FString& What, const FVector& Actual, const FVector& Expected);

    /** Gets how long this test is allowed to run before it fails automatically, in seconds. */
    float GetTimeoutInSeconds() const;

    /** Event when this test has finished successfully. */
    virtual void NotifyOnTestSuccessful();

    /** Event when this test has failed. */
    virtual void NotifyOnTestFailed(const FString& Message);

    /** Event when this test has been skipped. */
    virtual void NotifyOnTestSkipped();

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
    FDaeTestActorTestSuccessfulSignature OnTestSuccessful;

    /** Event when this test has failed. */
    FDaeTestActorTestFailedSignature OnTestFailed;

    /** Event when this test has been skipped. */
    FDaeTestActorTestSkippedSignature OnTestSkipped;

private:
    static const FString ErrorMessageFormat;

    /** How long this test is allowed to run before it fails automatically, in seconds. */
    UPROPERTY(EditAnywhere)
    float TimeoutInSeconds;

    /** Reason for skipping this test. Test will be skipped if this is not empty. Useful for temporarily disabling unstable tests. */
    UPROPERTY(EditAnywhere)
    FString SkipReason;

    /** Whether this test has finished executing (either with success or failure). */
    bool bHasResult;
};
