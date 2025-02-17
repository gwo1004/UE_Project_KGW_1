// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerGameFramework/PlayableController.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "DataAssets\InputConfigPrimaryDataAsset.h"
#include "DataAssets\DroneInputDataAsset.h"

APlayableController::APlayableController()
{
    CurrentMode = EControlMode::NONE;

	ControlModeMap.Add(EControlMode::TPSCharacter, FControlModeMapping());
	ControlModeMap.Add(EControlMode::FPSCharacter, FControlModeMapping());
	ControlModeMap.Add(EControlMode::DRONE, FControlModeMapping());
}

void APlayableController::BeginPlay()
{
	Super::BeginPlay();
}
	
void APlayableController::SetupInputComponent()
{
}

void APlayableController::SwitchControlMode(EControlMode Mode)
{
	if (ULocalPlayer* LocalPlayer = GetLocalPlayer())
	{
		if (UEnhancedInputLocalPlayerSubsystem* SubSystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			if (FControlModeMapping* ModeData = ControlModeMap.Find(Mode))
			{
				SubSystem->ClearAllMappings();
				SubSystem->AddMappingContext(ModeData->IMC, 0);
                CurrentMode = Mode;
			}
		}

	}
}

void APlayableController::UpdateCurrentIMC(UInputConfigPrimaryDataAsset* CurrentDataAsset)
{
    bool bHasPawn = (GetPawn() != nullptr);

    if (ULocalPlayer* LocalPlayer = GetLocalPlayer())
    {
        if (UEnhancedInputLocalPlayerSubsystem* SubSystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
        {
            for (auto& ControlMap : ControlModeMap)
            {
                if (ControlMap.Value.DataAsset == CurrentDataAsset)
                {
                    UInputMappingContext* NewIMC = NewObject<UInputMappingContext>(this);

                    for (const FPlayerDefaultInputKeyMapping& Mapping : CurrentDataAsset->KeyMappings)
                    {
                        if (Mapping.InputAction && Mapping.CurrentKey.IsValid())
                        {
                            FEnhancedActionKeyMapping& NewMapping = NewIMC->MapKey(Mapping.InputAction, Mapping.CurrentKey);
                            for (UInputModifier* Modifier : Mapping.Modifiers)
                            {
                                if (Modifier)
                                {
                                    NewMapping.Modifiers.Add(Modifier);
                                }
                            }
                        }
                    }

                    ControlMap.Value.IMC = NewIMC;
                    if (bHasPawn && ControlMap.Key == CurrentMode)
                    {
                        SubSystem->ClearAllMappings();
                        SubSystem->AddMappingContext(NewIMC, 0);
                    }
                }
            }
        }
    }
}
