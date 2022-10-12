// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "EnemySoldierAnimator.generated.h"

UCLASS(Blueprintable)
class UNBEATENCORTEGE_API UEnemySoldierAnimator : public UAnimInstance
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadOnly)
	class AEnemySoldier* Owner;

	UPROPERTY(BlueprintReadOnly)
	bool IsMoving;

	UPROPERTY(BlueprintReadWrite)
	bool IsResting;

	
	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float delta) override;
	
};
