// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameData/ABCharacterStat.h"
#include "ABCharacterStatComponent.generated.h"


DECLARE_MULTICAST_DELEGATE(FOnHpZeroDelegate);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHpChangedDelegate, float /* CurrentHp */ );

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ARENABATTLE_API UABCharacterStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UABCharacterStatComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	FORCEINLINE float GetCurrentHp() const { return CurrentHp; }
	FORCEINLINE int32 GetCurrentLevel() const { return CurrentLevel; }
	void SetCurrentLevel(int32 InNewLevel);
	FORCEINLINE void SetModifierStat(const FABCharacterStat& InModifierStat) { ModifierStat = InModifierStat; }
	FORCEINLINE FABCharacterStat GetTotalStat() const { return BaseStat + ModifierStat; }
	
	float ApplyDamage(float InDamage);
	
	FOnHpZeroDelegate OnHpZero;
	FOnHpChangedDelegate OnHpChanged;
	
private:
	void SetHp(float NewHp);

	// 오브젝트를 저장할 때 속성들이 모두 디스크에 저장됨
	// CurrentHp는 게임할 때마다 새롭게 지정하므로 디스크에 저장할 필요 없음
	// Transient : 디스크에 저장 X
	UPROPERTY(Transient, VisibleInstanceOnly, Category="Stat")
	float CurrentHp;
	
	UPROPERTY(Transient, VisibleInstanceOnly, Category="Stat")
	int32 CurrentLevel = 1;
	
	UPROPERTY(Transient, VisibleInstanceOnly, Category="Stat", Meta = (AllowPrivateAccess = "true"))
	FABCharacterStat BaseStat;
	
	UPROPERTY(Transient, VisibleInstanceOnly, Category="Stat", Meta = (AllowPrivateAccess = "true"))
	FABCharacterStat ModifierStat;
};
