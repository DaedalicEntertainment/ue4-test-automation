#include "DaeTestInputBlueprintFunctionLibrary.h"
#include "DaeTestLogCategory.h"
#include <InputCoreTypes.h>
#include <GameFramework/InputSettings.h>
#include <GameFramework/PlayerController.h>
#include <GameFramework/PlayerInput.h>
#include <Kismet/GameplayStatics.h>

void UDaeTestInputBlueprintFunctionLibrary::ApplyInputAction(
    UObject* Context, const FName& ActionName,
    EInputEvent InputEventType /*= EInputEvent::IE_Pressed*/)
{
    APlayerController* PlayerController = UGameplayStatics::GetPlayerController(Context, 0);

    const UInputSettings* InputSettings = GetDefault<UInputSettings>();

    for (const FInputActionKeyMapping& Mapping : InputSettings->GetActionMappings())
    {
        if (Mapping.ActionName == ActionName)
        {
            if (Mapping.bCtrl)
            {
                PlayerController->InputKey(EKeys::LeftControl, InputEventType, 0.0f, false);
            }
            if (Mapping.bAlt)
            {
                PlayerController->InputKey(EKeys::LeftAlt, InputEventType, 0.0f, false);
            }
            if (Mapping.bShift)
            {
                PlayerController->InputKey(EKeys::LeftShift, InputEventType, 0.0f, false);
            }
            if (Mapping.bCmd)
            {
                PlayerController->InputKey(EKeys::LeftCommand, InputEventType, 0.0f, false);
            }

            PlayerController->InputKey(Mapping.Key, InputEventType, 0.0f, false);
            return;
        }
    }

    UE_LOG(LogDaeTest, Error, TEXT("%s - Input action not found: %s"),
           IsValid(Context) ? *Context->GetName() : TEXT(""), *ActionName.ToString());
}

void UDaeTestInputBlueprintFunctionLibrary::ApplyInputAxis(UObject* Context, const FName& AxisName,
                                                           float AxisValue /*= 1.0f*/)
{
    APlayerController* PlayerController = UGameplayStatics::GetPlayerController(Context, 0);

    if (!IsValid(PlayerController))
    {
        return;
    }

    const UInputSettings* InputSettings = GetDefault<UInputSettings>();

    for (const FInputAxisKeyMapping& Mapping : InputSettings->GetAxisMappings())
    {
        if (Mapping.AxisName == AxisName)
        {
            PlayerController->InputAxis(Mapping.Key, AxisValue, 0.0f, 1, false);
            return;
        }
    }

    UE_LOG(LogDaeTest, Error, TEXT("%s - Input axis not found: %s"),
           IsValid(Context) ? *Context->GetName() : TEXT(""), *AxisName.ToString());
}
