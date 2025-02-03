// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveActors/MoveActorSpawner.h"
#include "MoveActors\SpawnActorDataAsset.h"
#include "MoveActors\MoveActorBase.h"

AMoveActorSpawner::AMoveActorSpawner()
{
	PrimaryActorTick.bCanEverTick = false;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SpawnDelayTime = 5.f;

	RandLocate = 500.f;
}

void AMoveActorSpawner::BeginPlay()
{
	Super::BeginPlay();
	SpawnActorWithDelay();
}

void AMoveActorSpawner::SpawnActorWithDelay()
{
	if (SpawnDelayTime != 0.f)
	{
		GetWorld()->GetTimerManager().SetTimer(SpawnDelayTimerHandle, this, &AMoveActorSpawner::SpawnActors, SpawnDelayTime, true);
	}
}

void AMoveActorSpawner::Destroy()
{
	if (IsPendingKillPending()) return;
	GetWorld()->GetTimerManager().ClearTimer(SpawnDelayTimerHandle);
}

void AMoveActorSpawner::SpawnActors()
{
	if (ActorSpawnDataAsset && !ActorSpawnDataAsset->ActorData.IsEmpty())
	{
		int32 RandDataAssetIndex = FMath::RandRange(0, ActorSpawnDataAsset->ActorData.Num() - 1);
		SpawnActorSettingWithRand(ActorSpawnDataAsset->ActorData[RandDataAssetIndex]);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("SpawnDataAsset Is Empty / Nullptr"));
	}

}

void AMoveActorSpawner::SpawnActorSettingWithRand(TSubclassOf<AMoveActorBase>& SpawnData)
{
	FVector SpawnLocation = GetActorLocation() + FMath::FRandRange(-RandLocate, RandLocate);
	FRotator SpawnRotation = GetActorRotation() + FRotator(FMath::FRandRange(0.f, 360.f));

	AMoveActorBase* SpawnActor = GetWorld()->SpawnActorDeferred<AMoveActorBase>(SpawnData, FTransform(SpawnRotation, SpawnLocation), this, nullptr, ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn);

	if (SpawnActor)
	{
		SpawnActor->bIsSpawnLimit = true;
		SpawnActor->SpawnDuration = FMath::FRandRange(5.f, 30.f);
		SpawnActor->CurrentDirection = FVector(FMath::RandRange(0, 1), FMath::RandRange(0, 1), FMath::RandRange(0, 1));

		SpawnActor->FinishSpawning(FTransform(SpawnRotation, SpawnLocation));
	}
}
