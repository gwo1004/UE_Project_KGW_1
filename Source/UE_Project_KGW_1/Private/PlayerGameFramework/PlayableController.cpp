// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerGameFramework/PlayableController.h"
#include "EnhancedInputSubsystems.h"
#include "DataAssets\DroneInputDataAsset.h"


APlayableController::APlayableController()
{
	IMCMap.Add(EControlMode::TPSCharacter, nullptr);
	IMCMap.Add(EControlMode::FPSCharacter, nullptr);
	IMCMap.Add(EControlMode::DRONE, nullptr);

	IAMap.Add(EControlMode::TPSCharacter, nullptr);
	IAMap.Add(EControlMode::FPSCharacter, nullptr);
	IAMap.Add(EControlMode::DRONE, nullptr);
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
			SubSystem->ClearAllMappings();
			SubSystem->AddMappingContext(IMCMap[Mode], 0);
		}
	}
}