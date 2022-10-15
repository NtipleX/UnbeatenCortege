// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Animation/AnimMontage.h"
#include "nxAnimator.generated.h"

UCLASS(Blueprintable)
class UNBEATENCORTEGE_API UnxAnimator : public UAnimInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = nx)
	UAnimMontage* animMontage;

	UnxAnimator();

protected:
	virtual void NativeUpdateAnimation(float delta) override;

private:
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	class AnxHero* m_owner;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	bool m_startedPlaying;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	float heroVelocity;
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	float xHeroVelocity;
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	float yHeroVelocity;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	float xReturn;
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	float yReturn;
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	float xVelocity;

};
