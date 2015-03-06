// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Controller.h"
#include "HeroCharacter.h"
#include "BossCharacter.h"
#include "SkeletonKing.generated.h"

/**
 * 
 */
UCLASS()
class ASkeletonKing : public AController
{
	GENERATED_BODY()
	ASkeletonKing(const FObjectInitializer& ObjectInitializer);

	protected:	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	private:
	AHeroCharacter* _heroCharacter;
	ABossCharacter* _bossCharacter;
	float _currentTime;
	bool _isChasing;
	
};
