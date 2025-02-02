// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IMoveActors.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UIMoveActors : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class UE_PROJECT_KGW_1_API IIMoveActors
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	virtual void OnActorBeginOverlap() = 0;
	virtual void OnActorEndOverlap() = 0;

	virtual void ActivateActor(float DeltaTime) = 0;
	virtual void SpawnActorDurationLimitTime() = 0;
};
