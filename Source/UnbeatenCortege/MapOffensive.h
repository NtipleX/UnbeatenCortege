#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MapOffensive.generated.h"

UCLASS()
class UNBEATENCORTEGE_API AMapOffensive: public AActor
{
	GENERATED_BODY()
		
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int MaxPerLevel;
};

