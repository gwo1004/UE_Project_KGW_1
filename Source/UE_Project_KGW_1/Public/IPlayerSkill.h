// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IPlayerSkill.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UIPlayerSkill : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class UE_PROJECT_KGW_1_API IIPlayerSkill
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	// TPS
	virtual void TPSMainSkill() = 0;
	virtual void TPSFirstSkill() = 0;
	virtual void TPSSecondSubSkill() = 0;
	virtual void TPSUltSkill() = 0;

	// FPS
	virtual void FPSMainSkill() = 0;
};
