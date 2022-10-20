// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "BerserkAnimator.generated.h"

/**
 * 
 */
UCLASS()
class UNBEATENCORTEGE_API UBerserkAnimator : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	virtual void NativeUpdateAnimation(float delta) override;


};
