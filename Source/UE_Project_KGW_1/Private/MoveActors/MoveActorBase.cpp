// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveActors/MoveActorBase.h"
#include "MoveActors\StaticMeshDataAsset.h"

AMoveActorBase::AMoveActorBase()
{
 	PrimaryActorTick.bCanEverTick = true;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	RootComponent = SceneRoot;

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComp->SetupAttachment(SceneRoot);

	static ConstructorHelpers::FObjectFinder<UStaticMeshDataAsset> DataAssetFinder
	(TEXT("/Game/Blueprints/MoveActors/BP_StaticMeshDataAsset.BP_StaticMeshDataAsset"));

	if (DataAssetFinder.Succeeded())
	{
		MeshDataAsset = DataAssetFinder.Object;
		ApplyMeshAsset(0);
	}

	MoveVelocity = 100.0f;
	SpawnDuration = 30.0f;
	bIsSpawnLimit = false;
}

void AMoveActorBase::BeginPlay()
{
	Super::BeginPlay();

	CurrentLocation = GetActorLocation();

	if (bIsSpawnLimit)
	{
		SpawnActorDurationLimitTime();
	}
}

void AMoveActorBase::SpawnActorDurationLimitTime()
{
	GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle, this, &AMoveActorBase::DestroyActor, SpawnDuration, false);
}

void AMoveActorBase::DestroyActor()
{
	if (IsPendingKillPending()) return;

	if (GetWorld())
	{
		GetWorld()->GetTimerManager().ClearTimer(SpawnTimerHandle);
	}

	if (StaticMeshComp)
	{
		StaticMeshComp->DestroyComponent();
		StaticMeshComp = nullptr;
	}

	if (SceneRoot)
	{
		SceneRoot->DestroyComponent();
		SceneRoot = nullptr;
	}

	if (MeshDataAsset)
	{
		MeshDataAsset = nullptr;
	}

	Destroy();
}

void AMoveActorBase::ApplyMeshAsset(int32 Index)
{
	if (MeshDataAsset && MeshDataAsset->StaticMeshAssetList.IsValidIndex(Index))
	{
		StaticMeshComp->SetStaticMesh(MeshDataAsset->StaticMeshAssetList[Index]);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("MeshDataAsset Not Valid"));
	}
}
