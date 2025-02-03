// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MoveActorSpawner.generated.h"

class USpawnActorDataAsset;
class AMoveActorBase;

UCLASS()
class UE_PROJECT_KGW_1_API AMoveActorSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	AMoveActorSpawner();

protected:
	virtual void BeginPlay() override;
	void SpawnActorWithDelay();
	void Destroy();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner")
	USpawnActorDataAsset* ActorSpawnDataAsset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner")
	float SpawnDelayTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner")
	float RandLocate;

private:
	FTimerHandle SpawnDelayTimerHandle;

private:
	void SpawnActors();
	void SpawnActorSettingWithRand(TSubclassOf<AMoveActorBase>& SpawnData);
};
