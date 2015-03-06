// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "SkeletonPuzzleSlamCharacter.h"
#include "BossCharacter.generated.h"

UCLASS(Blueprintable)
class ABossCharacter : public ASkeletonPuzzleSlamCharacter
{
	GENERATED_UCLASS_BODY()
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
