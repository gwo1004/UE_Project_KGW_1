// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "MoveActors/MoveActorBase.h"
#include "SpawnActorDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class UE_PROJECT_KGW_1_API USpawnActorDataAsset : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category ="Actor Spawn Data")
	TArray<TSubclassOf<AMoveActorBase>> ActorData;
};
