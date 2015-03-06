// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "SkeletonPuzzleSlam.h"
#include "SkeletonPuzzleSlamGameMode.h"
#include "SkeletonPuzzleSlamPlayerController.h"
#include "SkeletonPuzzleSlamCharacter.h"
#include "MyGameState.h"
#include "SkeletonKing.h"

ASkeletonPuzzleSlamGameMode::ASkeletonPuzzleSlamGameMode(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	// use our custom PlayerController class
	PlayerControllerClass = ASkeletonPuzzleSlamPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/HeroBlueprint"));
	//static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDown/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
		UE_LOG(LogTemp, Log, TEXT("Game Mode"));
	}

	GameStateClass = AMyGameState::StaticClass();
}

void ASkeletonPuzzleSlamGameMode::BeginPlay()
{
	Super::BeginPlay();
	// spawn actor
	GetWorld()->SpawnActor(ASkeletonKing::StaticClass());
}

void ASkeletonPuzzleSlamGameMode::InitGameState()
{
	Super::InitGameState();

	// get the game state
	//check for null ptr

	//set values to the gamestate
	//set the game state's state machine
}

void ASkeletonPuzzleSlamGameMode::EndGame(EGameplayVictor::Type victor)
{
	// we'll do something based on victory conditions
	switch (victor)
	{
		case EGameplayVictor::NotPlayer:
			// the boss crushed your face in
			break;
		case EGameplayVictor::Player:
			// damn son you won
			break;
	}
}
