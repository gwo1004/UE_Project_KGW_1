// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveActors/LocateMoveActor.h"

ALocateMoveActor::ALocateMoveActor()
{
	MoveMaxRange = 1000.f;
	WaitTime = 1.5f;
	MoveDistance = 0.f;
	bIsMove = true;
	MoveVelocity = 400.f;
	CurrentDirection = FVector(1.0f, 0.f, 0.f);
}

void ALocateMoveActor::BeginPlay()
{
	Super::BeginPlay();
	if (bIsSpawnLimit)
	{
		SpawnActorDurationLimitTime();
	}
}

void ALocateMoveActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ActivateActor(DeltaTime);
}

void ALocateMoveActor::OnActorBeginOverlap()
{
}

void ALocateMoveActor::OnActorEndOverlap()
{
}

void ALocateMoveActor::ActivateActor(float DeltaTime)
{
	if (!bIsMove) return;

	if (MoveDistance >= MoveMaxRange)
	{
		if (WaitTime != 0.f)
		{
			bIsMove = false;
			GetWorld()->GetTimerManager().SetTimer(MovementDelayTimerHandle, this, &ALocateMoveActor::ResumeMovement, WaitTime, false);
		}
		CurrentDirection = -CurrentDirection;
		MoveDistance = 0.f;
	}

	FVector Move(CurrentDirection * MoveVelocity * DeltaTime);
	CurrentLocation += Move;
	AddActorLocalOffset(Move);
	MoveDistance += Move.Size();
}

void ALocateMoveActor::SpawnActorDurationLimitTime()
{
	Super::SpawnActorDurationLimitTime();
}

void ALocateMoveActor::DestroyActor()
{
	if (IsPendingKillPending()) return;

	Super::DestroyActor();

	GetWorld()->GetTimerManager().ClearTimer(MovementDelayTimerHandle);
}

void ALocateMoveActor::ResumeMovement()
{
	bIsMove = true;
}
