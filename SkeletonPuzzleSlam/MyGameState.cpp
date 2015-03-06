// Fill out your copyright notice in the Description page of Project Settings.

#include "SkeletonPuzzleSlam.h"
#include "MyGameState.h"




AMyGameState::AMyGameState(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer), _puzzleStartTime(0), _puzzleStarted(false), _puzzleSolved(false)
{

}

void AMyGameState::OnActorDied(class ASkeletonPuzzleSlamCharacter* InChar)
{
	
}

void AMyGameState::OnActorSpawned(class ASkeletonPuzzleSlamCharacter* InChar)
{
	if (InChar->Tags[0].ToString() == FString(TEXT("Hero")))
	{
		_heroCharacter = Cast<AHeroCharacter>(InChar);
		UE_LOG(LogTemp, Log, TEXT("Hero Character Registered"));
	}

	if (InChar->Tags[0].ToString() == FString(TEXT("Boss")))
	{
		_bossCharacter = Cast<ABossCharacter>(InChar);
		UE_LOG(LogTemp, Log, TEXT("Boss Character Registered"));
	}
}

void AMyGameState::OnActorDamaged(class AActor* InActor, float Damage, class AController* EventInstigator)
{

}

void AMyGameState::StartGameplayStateMachine()
{

}

void AMyGameState::OnGameStart()
{

}

void AMyGameState::FinishGame()
{

}

void AMyGameState::RegisterPuzzleTrigger(APuzzleTrigger* trigger)
{
	_triggers.Add(trigger);
	UE_LOG(LogTemp, Log, TEXT("Puzzle Trigger Added."));
}

void AMyGameState::PlayerSteppedOnPuzzleTrigger(APuzzleTrigger* trigger)
{
	// don't restart puzzle
	if (_puzzleSolved)
		return;

	// has the puzzle been started?
	if (!_puzzleStarted)
	{
		// set the start time
		_puzzleStartTime = GetWorld()->GetTimeSeconds();
	}

	// check if time hasn't expired
	if (GetWorld()->GetTimeSeconds() < _puzzleStartTime + 45) // you have 45 seconds
	{
		// a trigger was stepped on, we'll add it to a list
		_steppedOnTriggers.Add(trigger->NameTag);

		// if the triggers total up to 6, we check
		if (_steppedOnTriggers.Num() == 6) // anticipate 6 items max
		{
			// the order for shield is 1, 2, 3, 4, 5, 6
			bool puzzleSuccess = true;
			if (_steppedOnTriggers[0].ToString() == FString(TEXT("1")))
			{
				puzzleSuccess &= true;
			}
			else
			{
				puzzleSuccess &= false;
			}

			if (_steppedOnTriggers[1].ToString() == FString(TEXT("2")))
			{
				puzzleSuccess &= true;
			}
			else
			{
				puzzleSuccess &= false;
			}

			if (_steppedOnTriggers[2].ToString() == FString(TEXT("3")))
			{
				puzzleSuccess &= true;
			}
			else
			{
				puzzleSuccess &= false;
			}

			if (_steppedOnTriggers[3].ToString() == FString(TEXT("4")))
			{
				puzzleSuccess &= true;
			}
			else
			{
				puzzleSuccess &= false;
			}

			if (_steppedOnTriggers[4].ToString() == FString(TEXT("5")))
			{
				puzzleSuccess &= true;
			}
			else
			{
				puzzleSuccess &= false;
			}

			if (_steppedOnTriggers[5].ToString() == FString(TEXT("6")))
			{
				puzzleSuccess &= true;
			}
			else
			{
				puzzleSuccess &= false;
			}

			if (puzzleSuccess)
			{
				// unlock shield
				_shieldPickup->EnablePickup();
				UE_LOG(LogTemp, Log, TEXT("Puzzle Solved"));
				_puzzleSolved = true;
			}
			else
			{
				// reset puzzle
				ResetPuzzle();
			}
		}
		else
		{
			UE_LOG(LogTemp, Log, TEXT("Puzzle in progress"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Puzzle reset"));
		ResetPuzzle();
		// puzzle is over, go through each trigger and set their stepped on values to false
	}
}

void AMyGameState::RegisterShieldPickup(AShieldPickup* shield)
{
	_shieldPickup = shield;
}

void AMyGameState::ResetPuzzle()
{
	_steppedOnTriggers.Empty();
	_puzzleStarted = false;
}
