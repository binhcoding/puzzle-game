// Enum class

#include "GameTypes.generated.h"
#pragma once

namespace EGameplayVictor
{
	enum Type
	{
		Player,
		NotPlayer
	};
}

namespace EPawn
{
	enum Type
	{
		Player,
		Boss
	};
}

USTRUCT()
struct FBuffData
{
	GENERATED_USTRUCT_BODY()

	// Attack Damage
	UPROPERTY(EditDefaultsOnly, Category = Data)
	int32 Attack;

	FBuffData()
	{
		// defaults
		Attack = 5;
	}
};