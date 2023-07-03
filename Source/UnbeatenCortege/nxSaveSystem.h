// Conquested Path. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "nxSaveSystem.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EPurchaseProduct : uint8
{
	AdaptiveCompressor
};

UCLASS()
class UNBEATENCORTEGE_API UnxSaveSystem : public USaveGame
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	static void SaveProgress(int32 money);
	static void SaveEditProgress(UnxSaveSystem* obj);
	UFUNCTION(BlueprintCallable)
	static UnxSaveSystem* RetriveProgress();

	UFUNCTION(BlueprintCallable)
	static void MakePurchase(EPurchaseProduct Product, int32 price);

	UPROPERTY(BlueprintReadOnly)
	int32 money;

	UPROPERTY(BlueprintReadOnly)
	TArray<EPurchaseProduct> purchases;

private:
	
};
