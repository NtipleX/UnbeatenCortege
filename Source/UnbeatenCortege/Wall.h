#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Wall.generated.h"

UCLASS(Blueprintable)
class UNBEATENCORTEGE_API UWall : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:	
	UWall();
	void GetDamage();
	FORCEINLINE float GetHealth() const;

protected:
	//virtual void BeginPlay() override;
	//virtual void Tick(float DeltaTime) override;
	//virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

private:
	UPROPERTY(EditDefaultsOnly, Category = nx, meta = (AllowPrivateAccess = true))
	UMaterial* darkenMaterial;

	UPROPERTY(EditDefaultsOnly)
	class UBoxComponent* wallBox;

	UPROPERTY(EditDefaultsOnly)
	class USoundCue* hitSound;
	UPROPERTY(EditDefaultsOnly)
	USoundCue* destroySound;

	float m_health;

};
