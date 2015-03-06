// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "ShieldPickup.generated.h"

UCLASS()
class SKELETONPUZZLESLAM_API AShieldPickup : public AActor
{
	GENERATED_BODY()
	
public:	
	AShieldPickup(const FObjectInitializer& ObjectInitializer);
	void EnablePickup();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBoxComponent* BoxComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* ShieldMesh;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;	
	virtual void ReceiveActorBeginOverlap(AActor* OtherActor) override;
	private:
	bool _pickupEnabled;
};
