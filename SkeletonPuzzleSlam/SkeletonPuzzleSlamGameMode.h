// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/GameMode.h"
#include "GameTypes.h"
#include "SkeletonPuzzleSlamGameMode.generated.h"

UCLASS(minimalapi)
class ASkeletonPuzzleSlamGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	ASkeletonPuzzleSlamGameMode(const FObjectInitializer& ObjectInitializer);
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// initialize the game state actor
	virtual void InitGameState() override;

	void EndGame(EGameplayVictor::Type victor);
};



