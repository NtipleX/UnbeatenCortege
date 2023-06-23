// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "nxHUD.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FConsumeLife);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAwardCoins, int, CoinsAward);

UCLASS()
class UNBEATENCORTEGE_API AnxHUD : public AHUD
{
	GENERATED_BODY()
		
public:
	
	UPROPERTY(BlueprintAssignable)
	FConsumeLife OnConsumeLife;

	UPROPERTY(BlueprintAssignable, VisibleAnywhere)
	FAwardCoins OnAwardCoins;

};
