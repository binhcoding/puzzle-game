#include "SkeletonPuzzleSlam.h"
#include "BossCharacter.h"
#include "MyGameState.h"

ABossCharacter::ABossCharacter(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

}

void ABossCharacter::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Log, TEXT("I Live to Slaughter."));

	// register yourself
	AMyGameState* gameState = Cast<AMyGameState>(GetWorld()->GameState);
	if (gameState)
	{
		gameState->OnActorSpawned(this);
	}
}


