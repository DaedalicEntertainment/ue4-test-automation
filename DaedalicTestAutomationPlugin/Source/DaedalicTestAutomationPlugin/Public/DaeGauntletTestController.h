#pragma once

#include <CoreMinimal.h>
#include <GauntletTestController.h>
#include "DaeGauntletTestController.generated.h"

class ADaeTestSuiteActor;

/** Controller for automated tests run by Gauntlet. */
UCLASS()
class DAEDALICTESTAUTOMATIONPLUGIN_API UDaeGauntletTestController : public UGauntletTestController
{
    GENERATED_BODY()

public:
    virtual void OnInit() override;
    virtual void OnPostMapChange(UWorld* World) override;
    virtual void OnTick(float TimeDelta) override;

private:
    TArray<FName> MapNames;
    int32 MapIndex;

    void LoadNextTestMap();

    UFUNCTION()
    void OnTestSuiteSuccessful(ADaeTestSuiteActor* TestSuite);

    UFUNCTION()
    void OnTestSuiteFailed(ADaeTestSuiteActor* TestSuite);
};
