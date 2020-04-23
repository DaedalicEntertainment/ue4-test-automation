#pragma once

#include <CoreMinimal.h>
#include <GameFramework/Actor.h>
#include "DaeGauntletTestSuiteActor.generated.h"

class ADaeGauntletTestActor;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDaeGauntletTestSuiteActorTestSuiteSuccessfulSignature,
                                            ADaeGauntletTestSuiteActor*, TestSuite);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDaeGauntletTestSuiteActorTestSuiteFailedSignature,
                                            ADaeGauntletTestSuiteActor*, TestSuite);

/** Collection of automated tests. */
UCLASS()
class DAEDALICTESTAUTOMATIONPLUGIN_API ADaeGauntletTestSuiteActor : public AActor
{
    GENERATED_BODY()

public:
    ADaeGauntletTestSuiteActor(
        const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

    virtual void BeginPlay() override;

    /** Runs all tests of this suite, in order. */
    void RunAllTests();

    /** Whether this test suite is currently running. */
    bool IsRunning() const;

    /** Event when this test suite has successfully finished all tests. */
    FDaeGauntletTestSuiteActorTestSuiteSuccessfulSignature OnTestSuiteSuccessful;

    /** Event when any tests of this test suite have failed. */
    FDaeGauntletTestSuiteActorTestSuiteFailedSignature OnTestSuiteFailed;

private:
    /** Tests to run in this level. */
    UPROPERTY(EditInstanceOnly)
    TArray<ADaeGauntletTestActor*> Tests;

    /** Whether to automatically run this test suite on BeginPlay in Play In Editor. */
    UPROPERTY(EditInstanceOnly)
    bool bRunInPIE;

    /** Index of the current test. */
    int32 TestIndex;

    /** Runs the next test in this test suite. */
    void RunNextTest();

    UFUNCTION()
    void OnTestSuccessful(ADaeGauntletTestActor* Test);

    UFUNCTION()
    void OnTestFailed(ADaeGauntletTestActor* Test);
};
