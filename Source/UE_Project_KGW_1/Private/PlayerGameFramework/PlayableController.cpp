// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerGameFramework/PlayableController.h"
#include "EnhancedInputSubsystems.h"
#include "DataAssets\DroneInputDataAsset.h"


APlayableController::APlayableController() :
	InputMappingContext(nullptr),
	InputActions(nullptr)
{
}

void APlayableController::BeginPlay()
{
	Super::BeginPlay();
	
	if (ULocalPlayer* LocalPlayer = GetLocalPlayer())
	{
		if (UEnhancedInputLocalPlayerSubsystem* SubSystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			if (InputMappingContext)
			{
				SubSystem->AddMappingContext(InputMappingContext, 0);
			}
		}
	}

}

void APlayableController::SetupInputComponent()
{
}
