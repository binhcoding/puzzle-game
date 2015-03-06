// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "SkeletonPuzzleSlamCharacter.h"
#include "SwordActor.h"
#include "HeroCharacter.generated.h"

UCLASS(Blueprintable)
class AHeroCharacter : public ASkeletonPuzzleSlamCharacter
{
	GENERATED_UCLASS_BODY()

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	public:
	void EnableShield();

	protected:
	//Select this component and set the static mesh for the sword to render properly on game start.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* SwordComponent;
	
	//Select this component and set the static mesh for the shield to render properly on game start.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* ShieldComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = CharacterStuff)
	bool CanBlock;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = CharacterStuff)
	bool IsBlocking;
};
