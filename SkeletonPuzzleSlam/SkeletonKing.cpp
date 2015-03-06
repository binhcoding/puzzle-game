// Fill out your copyright notice in the Description page of Project Settings.

#include "SkeletonPuzzleSlam.h"
#include "SkeletonKing.h"
#include "MyGameState.h"




ASkeletonKing::ASkeletonKing(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer), _currentTime(0), _isChasing(false)
{
	PrimaryActorTick.bCanEverTick = true;
}

void ASkeletonKing::BeginPlay()
{
	// take over your the skeleton king pawn
}

void ASkeletonKing::Tick(float DeltaTime)
{
	// grab player reference
	if (!_heroCharacter)
	{
		AMyGameState* gameState = Cast<AMyGameState>(GetWorld()->GameState);
		if (gameState)
		{
			_heroCharacter = gameState->GetHeroCharacter();
		}
	}

	if (!_bossCharacter)
	{
		// getting a reference to my character im supposed to control
		AMyGameState* gameState = Cast<AMyGameState>(GetWorld()->GameState);
		if (gameState)
		{
			_bossCharacter = gameState->GetBossCharacter();
			// POSSESS THIS
			Possess(_bossCharacter);
		}
	}

	if (_bossCharacter && _heroCharacter)
	{
		
		//float distanceBetweenTwoCharacters = Dist(_bossCharacter->GetActorLocation(), _heroCharacter->GetActorLocation());
		FVector vectorBetweenTwoActors = _bossCharacter->GetActorLocation() - _heroCharacter->GetActorLocation();
		if (vectorBetweenTwoActors.Size() < 500 && !_isChasing)
		{
			UE_LOG(LogTemp, Log, TEXT("Destroy the hero"));
			// direct him
			// move him towards the other actor using the navmesh
			_isChasing = true;
			UNavigationSystem* const NavSys = GetWorld()->GetNavigationSystem();
			if (NavSys)
			{
				FVector destLocation = _heroCharacter->GetActorLocation();
				NavSys->SimpleMoveToLocation(this, destLocation);
			}

		}

		if (_currentTime < GetWorld()->GetTimeSeconds())
		{
			UE_LOG(LogTemp, Log, TEXT("Distance between two actors, %f"), vectorBetweenTwoActors.Size());
		}
	}

	if (_currentTime < GetWorld()->GetTimeSeconds())
	{
		_currentTime = GetWorld()->GetTimeSeconds() + 3;
		UE_LOG(LogTemp, Log, TEXT("Status of my variables"));

		if (_heroCharacter)
		{
			UE_LOG(LogTemp, Log, TEXT("Hero Registered"));
		}

		if (_bossCharacter)
		{
			UE_LOG(LogTemp, Log, TEXT("Boss Registered"));
		}
	}

}
