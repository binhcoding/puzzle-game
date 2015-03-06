// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameState.h"
#include "SkeletonPuzzleSlamCharacter.h"
#include "PuzzleTrigger.h"
#include "ShieldPickup.h"
#include "BossCharacter.h"
#include "HeroCharacter.h"
#include "MyGameState.generated.h"

/**
 * 
 */
UCLASS()
class SKELETONPUZZLESLAM_API AMyGameState : public AGameState
{
	GENERATED_BODY()
	
	public:
	AMyGameState(const FObjectInitializer& ObjectInitializer);

	

	// notification that the player died
	void OnActorDied(class ASkeletonPuzzleSlamCharacter* InChar);
	// notification that the player spawned
	void OnActorSpawned(class ASkeletonPuzzleSlamCharacter* InChar);
	// notify which actor was damaged and by whom
	void OnActorDamaged(class AActor* InActor, float Damage, class AController* EventInstigator);

	void StartGameplayStateMachine();
	void OnGameStart();
	void FinishGame();

	void RegisterPuzzleTrigger(APuzzleTrigger* trigger);
	void PlayerSteppedOnPuzzleTrigger(APuzzleTrigger* trigger);
	void RegisterShieldPickup(AShieldPickup* shield);
	AHeroCharacter* GetHeroCharacter() const { return _heroCharacter; }
	ABossCharacter* GetBossCharacter() const { return _bossCharacter; }

	private:
	void ResetPuzzle();

	TArray<APuzzleTrigger*> _triggers;
	TArray<FName> _steppedOnTriggers;
	AShieldPickup* _shieldPickup;
	AHeroCharacter* _heroCharacter;
	ABossCharacter* _bossCharacter;

	float _puzzleStartTime;
	bool _puzzleStarted;
	bool _puzzleSolved;
	// the game has started
	// spawn the player, and boss from the game state
	// we'll track them here
	
};
