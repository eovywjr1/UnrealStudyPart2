// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interface/ABAnimationAttackInterface.h"
#include "ABCharacterBase.generated.h"

class UABCharacterControllData;

UENUM()
enum class ECharacterControlType : uint8
{
	Shoulder,
	Quater
};

UCLASS()
class ARENABATTLE_API AABCharacterBase : public ACharacter, public IABAnimationAttackInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AABCharacterBase();

protected:
	virtual void SetCharacterControlData(const UABCharacterControllData* CharacterControlData);

	UPROPERTY(EditAnywhere, Category = CharacterControl, Meta = (AllowPrivateAcess = "true"))
	TMap<ECharacterControlType, UABCharacterControllData*> CharacterControlManager;

// Combo Action Section
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	TObjectPtr<class UAnimMontage> ComboActionMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UABComboActionData> ComboActionData;

	void ProcessComboCommand();

	void ComboActionBegin();
	void ComboActionEnd(class UAnimMontage* TargetMontage, bool IsProperlyEnded);
	void SetComboCheckTimer();
	void ComboCheck();

	uint8 CurrentCombo = 0;
	FTimerHandle ComboTimerHandle;
	bool bHasNextComboCommand = false;

// Attack Hit Section
private:
	virtual void AttackHitCheck() override;

	// EventInstigator : 가해자, DamageCauser : 가해자의 무기나 폰 액터
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

// Dead Section
protected:
	virtual void SetDead();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Stat, Meta = (AllowPrivateAcess = "true"))
	TObjectPtr<class UAnimMontage> DeadActionMontage;

	float DeadEventDelayTime = 5.0f;

private:
	void PlayDeadAnimation();
};
