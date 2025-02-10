// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/AnimInstanceCharacterBase.h"
#include "GameFramework\Character.h"
#include "GameFramework\CharacterMovementComponent.h"
#include "PlayerableCharacterBase.h"

UAnimInstanceCharacterBase::UAnimInstanceCharacterBase()
{
	WeaponType = EWeaponType::Melee;
	Speed = 0.f;
	bIsJump = false;
	bIsCrouch = false;

}

void UAnimInstanceCharacterBase::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	APawn* Owner = TryGetPawnOwner();

	if (!Owner) return;
	
	Speed = Owner->GetVelocity().Size();
	Direction = CalculateDirection(Owner->GetVelocity(), Owner->GetActorRotation());

	APlayerableCharacterBase* Player = Cast<APlayerableCharacterBase>(Owner);
	if (!Player) return;
	bIsJump = Player->GetCharacterMovement()->IsFalling();
//	bIsJump = Player->bPressedJump;
	bIsCrouch = Player->bIsCrouched;
	
}
