#pragma once

#include <CoreMinimal.h>
#include <GameFramework/Actor.h>
#include "DaeGauntletTestActor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDaeGauntletTestActorTestSuccessfulSignature,
                                            ADaeGauntletTestActor*, Test);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDaeGauntletTestActorTestFailedSignature,
                                            ADaeGauntletTestActor*, Test);

UCLASS()
class DAEDALICTESTAUTOMATIONPLUGIN_API ADaeGauntletTestActor : public AActor
{
    GENERATED_BODY()

public:
    /** Starts executing this test. */
    void RunTest();

    /** Finishes the current test as success. */
    UFUNCTION(BlueprintCallable)
    void TestSuccessful();

    /** Finishes the current test as failure. */
    UFUNCTION(BlueprintCallable)
    void TestFailed();

    /** Event when this test started executing. */
    virtual void NotifyOnTestStarted();

    /** Event when this test started executing. */
    UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "OnTestStarted"))
    void ReceiveOnTestStarted();

    /** Event when this test has finished successfully. */
    FDaeGauntletTestActorTestSuccessfulSignature OnTestSuccessful;

    /** Event when this test has failed. */
    FDaeGauntletTestActorTestFailedSignature OnTestFailed;
};
