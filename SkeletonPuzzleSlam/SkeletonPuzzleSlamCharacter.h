// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/Character.h"
#include "Attachment.h"
#include "GameTypes.h"
#include "SkeletonPuzzleSlamCharacter.generated.h"

UCLASS(Blueprintable)
class ASkeletonPuzzleSlamCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

public:
	ASkeletonPuzzleSlamCharacter(const FObjectInitializer& ObjectInitializer);

	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	virtual void Death(class AController* Killer, class AActor* DamageCauser);

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, 
	class AController* EventInstigator, class AActor* DamageCauser) override;

	void AssignAttachments(EPawn::Type type);

	float Attack();
	void Block();

	// getters
	UFUNCTION(BlueprintCallable, Category = CharacterStuff)
	int32 GetHealth() const;
	
	//current health of this character
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharacterStuff)
	float Health;

	protected:
	UPROPERTY()
	// Shield Attachment
	UAttachment* ShieldSlot;

	UPROPERTY()
	// weapon attachment
	UAttachment* WeaponSlot;

	/** melee anim */
	UPROPERTY(EditDefaultsOnly, Category = CharacterStuff)
	UAnimMontage* MeleeAnim;

	/** melee anim */
	UPROPERTY(EditDefaultsOnly, Category = CharacterStuff)
	UAnimMontage* BlockAnim;
};

