#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "nxStructure.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTriggerDelegate);

UCLASS()
class UNBEATENCORTEGE_API AnxStructure : public AActor
{
	GENERATED_BODY()
	
public:	

	UPROPERTY(BlueprintReadWrite)
	FTriggerDelegate destroyed;

	AnxStructure();


	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;


protected:

	/// Components
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	class UStaticMeshComponent* structMesh;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	class UWidgetComponent* structHealthbar;
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	class UBoxComponent* structBox;

	/// Properties
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	float m_health;

};
