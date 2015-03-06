// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "SkeletonPuzzleSlam.h"
#include "MygameState.h"
#include "SkeletonPuzzleSlamCharacter.h"

ASkeletonPuzzleSlamCharacter::ASkeletonPuzzleSlamCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->AttachTo(RootComponent);
	CameraBoom->bAbsoluteRotation = true; // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->RelativeRotation = FRotator(-60.f, 0.f, 0.f);
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->AttachTo(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	TArray<UStaticMeshComponent*> comps;

	GetComponents(comps);
	for (auto StaticMeshComponent : comps)
	{
		UE_LOG(LogTemp, Log, TEXT("Comp thing"));
	}

}

void ASkeletonPuzzleSlamCharacter::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void ASkeletonPuzzleSlamCharacter::MoveRight(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

void ASkeletonPuzzleSlamCharacter::Death(class AController* Killer, class AActor* DamageCauser)
{
	Health = FMath::Min(0.0f, Health);

	// notify the game state that this character died
	AMyGameState* const GameState = GetWorld()->GetGameState<AMyGameState>();
	if (GameState)
	{
		// check if valid pointer
		GameState->OnActorDied(this);
	}

	// if this character was controlled by AI, disable it

	// and start removing components/disabling it from here
}

float ASkeletonPuzzleSlamCharacter::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser)
{
	if (Health <= 0.0f)
	{
		return 0.0f;
	}

	// game rules can effect damage taken
	// but for this example there wont be one

	Health -= Damage;
	if (Health <= 0.0f)
	{
		Death(EventInstigator, DamageCauser);
	}

	// alert the game state when damage takes place
	AMyGameState* const GameState = GetWorld()->GetGameState<AMyGameState>();
	if (GameState)
	{
		// check if valid pointer
		GameState->OnActorDamaged(this, Damage, EventInstigator);
	}
	return Damage;
}

void ASkeletonPuzzleSlamCharacter::AssignAttachments(EPawn::Type type)
{
	switch (type)
	{
		case EPawn::Boss:
			break;
		case EPawn::Player:
			// assign sword and shield component and don't render the shield
			break;
	}
}

float ASkeletonPuzzleSlamCharacter::Attack()
{
	if (Health > 0.0f && MeleeAnim)
	{
		UE_LOG(LogTemp, Log, TEXT("Playing Animation"));
		return PlayAnimMontage(MeleeAnim);
	}
	UE_LOG(LogTemp, Log, TEXT("JK Not"));
	return 0.0f;
}

int32 ASkeletonPuzzleSlamCharacter::GetHealth() const
{
	return Health;
}

void ASkeletonPuzzleSlamCharacter::Block()
{
	if (Health > 0.0f)
	{
		PlayAnimMontage(BlockAnim);
	}
}
