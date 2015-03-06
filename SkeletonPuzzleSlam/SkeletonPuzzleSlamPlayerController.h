// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/PlayerController.h"
#include "SkeletonPuzzleSlamPlayerController.generated.h"

UCLASS()
class ASkeletonPuzzleSlamPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ASkeletonPuzzleSlamPlayerController(const FObjectInitializer& ObjectInitializer);

protected:
	/** True if the controlled character should navigate to the mouse cursor. */
	uint32 bMoveToMouseCursor : 1;

	// Begin PlayerController interface
	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;
	// End PlayerController interface

	/** Navigate player to the current mouse cursor location. */
	void MoveToMouseCursor();

	/** Navigate player to the current touch location. */
	void MoveToTouchLocation(const ETouchIndex::Type FingerIndex, const FVector Location);
	
	/** Navigate player to the given world location. */
	void SetNewMoveDestination(const FVector DestLocation);

	/** Input handlers for SetDestination action. */
	void OnSetDestinationPressed();
	void OnSetDestinationReleased();

	// Input handlers for MoveForward | MoveRight
	void MoveForward(float Value);
	void MoveRight(float Value);
	void AttackPressed();
	void AttackReleased();
	void BlockPressed();
	void BlockReleased();

	private:
	float MeleeAttackAnimationEndTime;
	bool IsPlayingAnimation;
};


