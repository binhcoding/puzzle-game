// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "SwordActor.generated.h"

UCLASS()
class SKELETONPUZZLESLAM_API ASwordActor : public AActor
{
	GENERATED_UCLASS_BODY()
	
public:	
	/** Static Mesh Comp, Set In BP Default Properties */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = StaticMeshComponents)
	UStaticMeshComponent* Sword;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	
	
};
