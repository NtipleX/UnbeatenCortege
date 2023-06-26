// Conquested Path. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "nxSaveSystem.generated.h"

/**
 * 
 */
UCLASS()
class UNBEATENCORTEGE_API UnxSaveSystem : public USaveGame
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	static void SaveProgress(int32 money);
	UFUNCTION(BlueprintCallable)
	static UnxSaveSystem* RetriveProgress();

	UPROPERTY(BlueprintReadOnly)
	int32 money;

private:
	
};
