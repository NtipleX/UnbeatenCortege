#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "nxGameMode.generated.h"

UCLASS()
class UNBEATENCORTEGE_API AnxGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class AMapOffensive* mapOffensive;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<class AnxStructure> mainStab;


	UFUNCTION(BlueprintImplementableEvent)
	void GameOverEvent();
	
	UFUNCTION(BlueprintImplementableEvent)
	void GameWinEvent();

	virtual void StartPlay() override;

};
