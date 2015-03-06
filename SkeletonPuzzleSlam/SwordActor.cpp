// Fill out your copyright notice in the Description page of Project Settings.

#include "SkeletonPuzzleSlam.h"
#include "SwordActor.h"


// Sets default values
ASwordActor::ASwordActor(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Sword = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Sword"));
	RootComponent = Sword;
}

// Called when the game starts or when spawned
void ASwordActor::BeginPlay()
{
	Super::BeginPlay();
	// assign the sword mesh from the project to the sword's mesh

	
}

// Called every frame
void ASwordActor::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

