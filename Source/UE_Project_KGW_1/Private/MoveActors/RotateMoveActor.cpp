// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveActors/RotateMoveActor.h"


ARotateMoveActor::ARotateMoveActor()
{
	ApplyMeshAsset(1);

	CurrentDirection = FVector(0.f, 1.0f, 0.f);
	MoveVelocity = 50.f;

	PivotLocation = FVector(0.f, 0.f, 0.f);
	Angle = 0.f;
	bDrawCircle = false;
}

void ARotateMoveActor::BeginPlay()
{
	Super::BeginPlay();

	if (bIsSpawnLimit)
	{
		SpawnActorDurationLimitTime();
	}
}

void ARotateMoveActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ActivateActor(DeltaTime);
}

void ARotateMoveActor::OnActorBeginOverlap()
{
}

void ARotateMoveActor::OnActorEndOverlap()
{
}

void ARotateMoveActor::ActivateActor(float DeltaTime)
{
	FRotator RotateVelocity(CurrentDirection.Rotation() * DeltaTime);
	AddActorLocalRotation(RotateVelocity);

	if (bDrawCircle)
	{
		CurrentLocation = GetActorLocation();
		float Radius = FVector::Distance(CurrentLocation, PivotLocation);

		Angle += FMath::DegreesToRadians(MoveVelocity) * DeltaTime;

		FVector MoveLocation(
			PivotLocation.X + Radius * FMath::Cos(Angle),
			PivotLocation.Y + Radius * FMath::Sin(Angle),
			CurrentLocation.Z
		);
		SetActorLocation(MoveLocation);
	}
}

void ARotateMoveActor::SpawnActorDurationLimitTime()
{
	Super::SpawnActorDurationLimitTime();
}

void ARotateMoveActor::DestroyActor()
{
	if (IsPendingKillPending()) return;

	Super::DestroyActor();
}
