// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "GameTypes.h"
#include "Attachment.generated.h"
/**
 * 
 */
UCLASS(Blueprintable)
class UAttachment : public UStaticMeshComponent
{
	GENERATED_UCLASS_BODY()

	// positive effects of this data
	UPROPERTY(EditDefaultsOnly, Category = Attachment)
	FBuffData Effect;

	// attach point on pawn
	UPROPERTY(EditDefaultsOnly, Category = Attachment)
	FName AttachPoint;
};
