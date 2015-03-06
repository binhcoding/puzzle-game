// Fill out your copyright notice in the Description page of Project Settings.

#include "SkeletonPuzzleSlam.h"
#include "PuzzleTrigger.h"
#include "HeroCharacter.h"
#include "MyGameState.h"

APuzzleTrigger::APuzzleTrigger(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer), _isSteppedOn(false)
{	
	BoxComponent = ObjectInitializer.CreateAbstractDefaultSubobject<UBoxComponent>(this, TEXT("Box"));
	RootComponent = BoxComponent;
}

// Called when the game starts or when spawned
void APuzzleTrigger::BeginPlay()
{
	Super::BeginPlay();
	
	// when the game starts, add yourselves to the game state to be tracked as we're going to check the order you were triggered in
	AMyGameState* gameState = Cast<AMyGameState>(GetWorld()->GameState);
	if (gameState)
	{
		// valid pointer sweet
		gameState->RegisterPuzzleTrigger(this);
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Casting Failed"));
	}
	
}


void APuzzleTrigger::ReceiveActorBeginOverlap(AActor* OtherActor)
{
	// see if the other actor is a hero character, if so flag the stepped on boolean to true
	AHeroCharacter* heroCharacter = Cast<AHeroCharacter>(OtherActor);
	if (heroCharacter && !_isSteppedOn)
	{
		// valid pointer
		_isSteppedOn = true;
		UE_LOG(LogTemp, Log, TEXT("Yea you stepped on me."));
		// you must alert the gamestate that you were stepped on with this trigger to start the timer
		AMyGameState* gameState = Cast<AMyGameState>(GetWorld()->GameState);
		if (gameState)
		{
			gameState->PlayerSteppedOnPuzzleTrigger(this);
		}
	}

}
