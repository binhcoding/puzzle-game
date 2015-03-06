// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "SkeletonPuzzleSlam.h"
#include "SkeletonPuzzleSlamCharacter.h"
#include "SkeletonPuzzleSlamPlayerController.h"
#include "GameTypes.h"
#include "AI/Navigation/NavigationSystem.h"

ASkeletonPuzzleSlamPlayerController::ASkeletonPuzzleSlamPlayerController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer), MeleeAttackAnimationEndTime(0), IsPlayingAnimation(false)
{
	UE_LOG(LogTemp, Log, TEXT("Player Controller"));
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
	// player controller init's after game mode
	// its safe to do some post init logic concerning pawn setup
	APawn* const Pawn = GetPawn();
	if (Pawn)
	{
		ASkeletonPuzzleSlamCharacter* character = Cast<ASkeletonPuzzleSlamCharacter>(Pawn);
		if (character)
		{
			character->AssignAttachments(EPawn::Player);
		}
	}
	// when the player spawns we'll spawn the pawn that we should be controlling
}

void ASkeletonPuzzleSlamPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	// keep updating the destination every tick while desired
	if (bMoveToMouseCursor)
	{
		MoveToMouseCursor();
	}
}

void ASkeletonPuzzleSlamPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	InputComponent->BindAction("Attack", IE_Pressed, this, &ASkeletonPuzzleSlamPlayerController::AttackPressed);
	InputComponent->BindAction("Attack", IE_Released, this, &ASkeletonPuzzleSlamPlayerController::AttackReleased);

	InputComponent->BindAction("Block", IE_Pressed, this, &ASkeletonPuzzleSlamPlayerController::BlockPressed);
	InputComponent->BindAction("Block", IE_Released, this, &ASkeletonPuzzleSlamPlayerController::BlockReleased);

	//// support touch devices 
	//InputComponent->BindTouch(EInputEvent::IE_Pressed, this, &ASkeletonPuzzleSlamPlayerController::MoveToTouchLocation);
	//InputComponent->BindTouch(EInputEvent::IE_Repeat, this, &ASkeletonPuzzleSlamPlayerController::MoveToTouchLocation);

	InputComponent->BindAxis("MoveForward", this, &ASkeletonPuzzleSlamPlayerController::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &ASkeletonPuzzleSlamPlayerController::MoveRight);
}

void ASkeletonPuzzleSlamPlayerController::MoveToMouseCursor()
{
	// Trace to see what is under the mouse cursor
	FHitResult Hit;
	GetHitResultUnderCursor(ECC_Visibility, false, Hit);

	if (Hit.bBlockingHit)
	{
		// We hit something, move there
		SetNewMoveDestination(Hit.ImpactPoint);
	}
}

void ASkeletonPuzzleSlamPlayerController::MoveToTouchLocation(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	FVector2D ScreenSpaceLocation(Location);

	// Trace to see what is under the touch location
	FHitResult HitResult;
	GetHitResultAtScreenPosition(ScreenSpaceLocation, CurrentClickTraceChannel, true, HitResult);
	if (HitResult.bBlockingHit)
	{
		// We hit something, move there
		SetNewMoveDestination(HitResult.ImpactPoint);
	}
}

void ASkeletonPuzzleSlamPlayerController::SetNewMoveDestination(const FVector DestLocation)
{
	APawn* const Pawn = GetPawn();
	if (Pawn)
	{
		UNavigationSystem* const NavSys = GetWorld()->GetNavigationSystem();
		float const Distance = FVector::Dist(DestLocation, Pawn->GetActorLocation());

		// We need to issue move command only if far enough in order for walk animation to play correctly
		if (NavSys && (Distance > 120.0f))
		{
			NavSys->SimpleMoveToLocation(this, DestLocation);
		}
	}
}

void ASkeletonPuzzleSlamPlayerController::OnSetDestinationPressed()
{
	// set flag to keep updating destination until released
	bMoveToMouseCursor = true;
}

void ASkeletonPuzzleSlamPlayerController::OnSetDestinationReleased()
{
	// clear flag to indicate we should stop updating the destination
	bMoveToMouseCursor = false;
}

void ASkeletonPuzzleSlamPlayerController::MoveForward(float Value)
{
	// get the pawn we're currently possessing, we're pasing our stuff to him
	APawn* Pawn = GetPawn();
	if (Pawn)
	{
		// see if this pawn is actually a character
		ASkeletonPuzzleSlamCharacter* character = Cast<ASkeletonPuzzleSlamCharacter>(Pawn);
		if (character)
		{
			// k it exist, forward event
			character->MoveForward(Value);
		}
	}
}

void ASkeletonPuzzleSlamPlayerController::MoveRight(float Value)
{
	// get the pawn we're currently possessing, we're pasing our stuff to him
	APawn* Pawn = GetPawn();
	if (Pawn)
	{
		// see if this pawn is actually a character
		ASkeletonPuzzleSlamCharacter* character = Cast<ASkeletonPuzzleSlamCharacter>(Pawn);
		if (character)
		{
			// k it exist, forward event
			character->MoveRight(Value);
		}
	}
}

void ASkeletonPuzzleSlamPlayerController::AttackPressed()
{
	// get the pawn we're currently possessing, we're pasing our stuff to him
	APawn* Pawn = GetPawn();
	if (Pawn)
	{
		// see if this pawn is actually a character
		ASkeletonPuzzleSlamCharacter* character = Cast<ASkeletonPuzzleSlamCharacter>(Pawn);
		if (character)
		{
			IsPlayingAnimation = GetWorld()->GetTimeSeconds() < MeleeAttackAnimationEndTime;
			if (!IsPlayingAnimation)
			{
				MeleeAttackAnimationEndTime = GetWorld()->GetTimeSeconds() + character->Attack();
				FString logString = "Melee Attack Animation Time: " + FString::SanitizeFloat(MeleeAttackAnimationEndTime);
				UE_LOG(LogTemp, Log, TEXT("%s"), *logString);
			}
		}
	}
}

void ASkeletonPuzzleSlamPlayerController::AttackReleased()
{

}

void ASkeletonPuzzleSlamPlayerController::BlockPressed()
{
	// get the pawn we're currently possessing, we're pasing our stuff to him
	APawn* Pawn = GetPawn();
	if (Pawn)
	{
		// see if this pawn is actually a character
		ASkeletonPuzzleSlamCharacter* character = Cast<ASkeletonPuzzleSlamCharacter>(Pawn);
		if (character)
		{
			character->Block();
		}
	}	
}

void ASkeletonPuzzleSlamPlayerController::BlockReleased()
{

}
