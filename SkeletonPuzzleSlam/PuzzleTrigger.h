// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "PuzzleTrigger.generated.h"

UCLASS()
class SKELETONPUZZLESLAM_API APuzzleTrigger : public AActor
{
	GENERATED_BODY()
	
public:	
	APuzzleTrigger(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBoxComponent* BoxComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName NameTag;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	bool IsSteppedOn()
	{
		return _isSteppedOn;
	}

	virtual void ReceiveActorBeginOverlap(AActor* OtherActor) override;

	private:
	bool _isSteppedOn;

	
	
};
