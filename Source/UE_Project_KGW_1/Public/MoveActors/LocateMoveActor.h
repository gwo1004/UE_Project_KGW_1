// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MoveActors/MoveActorBase.h"
#include "LocateMoveActor.generated.h"

/**
 * 
 */
UCLASS()
class UE_PROJECT_KGW_1_API ALocateMoveActor : public AMoveActorBase
{
	GENERATED_BODY()
	
public:
	ALocateMoveActor();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

public:
	virtual void OnActorBeginOverlap() override;
	virtual void OnActorEndOverlap() override;
	virtual void ActivateActor(float DeltaTime) override;
	virtual void SpawnActorDurationLimitTime() override;
	virtual void DestroyActor() override;
public:
	void ResumeMovement();

protected:
	FTimerHandle MovementDelayTimerHandle;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform Movement")	
	float MoveMaxRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform Movement")	
	float WaitTime;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Platform Logic")	
	float MoveDistance;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Platform Logic")	
	bool bIsMove;
};
