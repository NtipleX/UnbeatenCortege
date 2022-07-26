#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "nxDerby.generated.h"

UCLASS()
class UNBEATENCORTEGE_API AnxDerby : public AActor
{
	GENERATED_BODY()

private:

	UPROPERTY(EditDefaultsOnly)
	class UStaticMeshComponent* debryMesh;

	UPROPERTY(EditAnywhere, Category = nx)
	float debryStrenght;

public:	
	AnxDerby();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;


};
