#pragma once

#include "Barricade.h"
#include "MetalBarricade.generated.h"

UCLASS(Blueprintable)
class UNBEATENCORTEGE_API AMetalBarricade : public ABarricade
{
	GENERATED_BODY()

public:
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

};