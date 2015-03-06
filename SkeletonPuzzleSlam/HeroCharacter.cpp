// Fill out your copyright notice in the Description page of Project Settings.

#include "SkeletonPuzzleSlam.h"
#include "Attachment.h"
#include "HeroCharacter.h"
#include "MyGameState.h"

AHeroCharacter::AHeroCharacter(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	// Create a sword component, attached to the Mesh of Character class, and the socket defined on character property sheet
	SwordComponent = ObjectInitializer.CreateAbstractDefaultSubobject<UStaticMeshComponent>(this, TEXT("Sword"));
	SwordComponent->AttachParent = GetMesh();
	SwordComponent->AttachSocketName = "WeaponSocket";

	// Create a sword component, attached to the Mesh of Character class, and the socket defined on character property sheet
	ShieldComponent = ObjectInitializer.CreateAbstractDefaultSubobject<UStaticMeshComponent>(this, TEXT("Shield"));
	ShieldComponent->AttachParent = GetMesh();
	ShieldComponent->AttachSocketName = "ShieldSocket";	

	ShieldComponent->SetVisibility(false);
}

void AHeroCharacter::BeginPlay()
{
	Super::BeginPlay();	
	// register yourself
	AMyGameState* gameState = Cast<AMyGameState>(GetWorld()->GameState);
	if (gameState)
	{
		gameState->OnActorSpawned(this);
	}
}

void AHeroCharacter::EnableShield()
{
	ShieldComponent->SetVisibility(true);
	CanBlock = true;
	UE_LOG(LogTemp, Log, TEXT("I HAVE A SHIELD FUCKKK YEAAAA"));
}
