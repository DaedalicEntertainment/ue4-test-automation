#pragma once

#include <CoreMinimal.h>
#include <GauntletTestController.h>
#include "DaeGauntletTestController.generated.h"

class ADaeGauntletTestSuiteActor;

/** Controller for automated tests run by Gauntlet. */
UCLASS()
class DAEDALICTESTAUTOMATIONPLUGIN_API UDaeGauntletTestController : public UGauntletTestController
{
    GENERATED_BODY()

public:
    virtual void OnPostMapChange(UWorld* World) override;

private:
    UFUNCTION()
    void OnTestSuiteSuccessful(ADaeGauntletTestSuiteActor* TestSuite);

    UFUNCTION()
    void OnTestSuiteFailed(ADaeGauntletTestSuiteActor* TestSuite);
};
