#pragma once

#include <CoreMinimal.h>

/** Data about a single performance budget violation. */
class DAEDALICTESTAUTOMATIONPLUGIN_API FDaeTestPerformanceBudgetViolation
{
public:
    /** Last target point that we passed. */
    FString PreviousTargetPointName;

    /** Next target point we want to pass. */
    FString NextTargetPointName;

    /** World location where the budget violation occurred. */
    FVector CurrentLocation;

    /** Frames per second at the time of the budget violation. */
    float FPS;

    /** Time spent on the game thread during the last frame (in milliseconds). */
    float GameThreadTime;

    /** Time spent on the render thread during the last frame (in milliseconds). */
    float RenderThreadTime;

    /** Time spent on the GPU during the last frame (in milliseconds). */
    float GPUTime;

    /** Full path the screenshot was written to. */
    FString ScreenshotPath;
};
