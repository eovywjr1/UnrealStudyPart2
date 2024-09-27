// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/ABCharacterNonPlayer.h"

void AABCharacterNonPlayer::SetDead()
{
	Super::SetDead();

	FTimerHandle DeadTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(DeadTimerHandle, FTimerDelegate::CreateLambda([&]() { Destroy(); }), DeadEventDelayTime, false);
}
