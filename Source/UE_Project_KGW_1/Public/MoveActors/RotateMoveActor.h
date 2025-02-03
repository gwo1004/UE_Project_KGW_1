// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MoveActors/MoveActorBase.h"
#include "RotateMoveActor.generated.h"

/**
 * 
 */
UCLASS()
class UE_PROJECT_KGW_1_API ARotateMoveActor : public AMoveActorBase
{
	GENERATED_BODY()
	
public:
	ARotateMoveActor();

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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform Rotate")
	FVector PivotLocation;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Platform Rotate")
	float Angle;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Platform Rotate")
	bool bDrawCircle;
};
