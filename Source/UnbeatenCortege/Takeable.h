#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Takeable.generated.h"

UCLASS()
class UNBEATENCORTEGE_API ATakeable : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
	class UStaticMeshComponent* meshComp;
	UPROPERTY(EditDefaultsOnly)
	class UBoxComponent* boxComp;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FTransform MeshToSocketTransform;
	UPROPERTY(BlueprintReadWrite)
	AActor* specificActor;

public:
	ATakeable();
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void specificAction();

};