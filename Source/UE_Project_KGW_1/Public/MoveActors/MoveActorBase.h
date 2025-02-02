// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "IMoveActors.h"
#include "MoveActorBase.generated.h"

class UStaticMeshDataAsset;

UCLASS()
class UE_PROJECT_KGW_1_API AMoveActorBase : public AActor, public IIMoveActors
{
	GENERATED_BODY()
	
public:	
	AMoveActorBase();

protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
	USceneComponent* SceneRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
	UStaticMeshComponent* StaticMeshComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh Data Asset")
	UStaticMeshDataAsset* MeshDataAsset;

	FTimerHandle SpawnTimerHandle;

public:
	virtual void OnActorBeginOverlap() {};
	virtual void OnActorEndOverlap() {};
	virtual void ActivateActor(float DeltaTime) {};
	virtual void SpawnActorDurationLimitTime() override;
	virtual void DestroyActor();
	void ApplyMeshAsset(int32 Index);

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Platform Movement")
	FVector CurrentLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform Movement")
	FVector CurrentDirection;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform Movement")
	float MoveVelocity;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform Spawn")
	float SpawnDuration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform Spawn")
	bool bIsSpawnLimit;


};
