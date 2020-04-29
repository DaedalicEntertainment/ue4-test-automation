#pragma once

#include <CoreMinimal.h>
#include <Kismet/BlueprintFunctionLibrary.h>
#include "DaeTestBlueprintFunctionLibrary.generated.h"

/** Utility functions for automating tests. */
UCLASS()
class DAEDALICTESTAUTOMATIONPLUGIN_API UDaeTestBlueprintFunctionLibrary
    : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    /** Triggers the output link after the specified number of frames. */
    UFUNCTION(BlueprintCallable,
              meta = (Latent, WorldContext = "WorldContextObject", LatentInfo = "LatentInfo"))
    static void DelayFrames(UObject* WorldContextObject, struct FLatentActionInfo LatentInfo,
                            int32 NumFrames = 1);
};
