// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
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
	FORCEINLINE float GetMaxHp() const { return MaxHp; }
	FORCEINLINE float GetCurrentHp() const { return CurrentHp; }

	float ApplyDamage(float InDamage);
	
	FOnHpZeroDelegate OnHpZero;
	FOnHpChangedDelegate OnHpChanged;
	
protected:
	
	void SetHp(float NewHp);
	
	// VisibleInstanceOnly : 인스턴스마다 다른 값 설정 가능
	UPROPERTY(VisibleInstanceOnly, Category="Stat")
	float MaxHp;

	// 오브젝트를 저장할 때 속성들이 모두 디스크에 저장됨
	// CurrentHp는 게임할 때마다 새롭게 지정하므로 디스크에 저장할 필요 없음
	// Transient : 디스크에 저장 X
	UPROPERTY(Transient, VisibleInstanceOnly, Category="Stat")
	float CurrentHp;
};
