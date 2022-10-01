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

public:
	virtual void StartPlay() override;

};
