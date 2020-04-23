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
    virtual void OnPostMapChange(UWorld* World) override;

private:
    UFUNCTION()
    void OnTestSuiteSuccessful(ADaeTestSuiteActor* TestSuite);

    UFUNCTION()
    void OnTestSuiteFailed(ADaeTestSuiteActor* TestSuite);
};
