// Fill out your copyright notice in the Description page of Project Settings.

#include "SkeletonPuzzleSlam.h"
#include "ShieldPickup.h"
#include "HeroCharacter.h"
#include "MyGameState.h"

AShieldPickup::AShieldPickup(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer), _pickupEnabled(false)
{
	BoxComponent = ObjectInitializer.CreateAbstractDefaultSubobject<UBoxComponent>(this, TEXT("Box"));
	ShieldMesh = ObjectInitializer.CreateAbstractDefaultSubobject<UStaticMeshComponent>(this, TEXT("Mesh"));
	RootComponent = ShieldMesh;
	BoxComponent->AttachTo(ShieldMesh);
}

void AShieldPickup::EnablePickup()
{
	_pickupEnabled = true;
	ShieldMesh->SetVisibility(true);
}

// Called when the game starts or when spawned
void AShieldPickup::BeginPlay()
{
	Super::BeginPlay();
	ShieldMesh->SetVisibility(false);
	AMyGameState* gameState = Cast<AMyGameState>(GetWorld()->GameState);
	if (gameState)
	{
		gameState->RegisterShieldPickup(this);
	}
}

void AShieldPickup::ReceiveActorBeginOverlap(AActor* OtherActor)
{
	if (_pickupEnabled)
	{
		// see if the other actor is a hero character, if so flag the stepped on boolean to true
		AHeroCharacter* heroCharacter = Cast<AHeroCharacter>(OtherActor);
		if (heroCharacter)
		{
			// UNLOCK HIS SHIELD BRUHHHHHHHHHHHH
			heroCharacter->EnableShield();
			Destroy();
		}
	}
}
