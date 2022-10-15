#include "nxAnimator.h"
#include "nxHero.h"

UnxAnimator::UnxAnimator()
	: m_startedPlaying(false)
	, heroVelocity(0.f)
{}

void UnxAnimator::NativeUpdateAnimation(float delta)
{
	Super::NativeUpdateAnimation(delta);
	if (!m_owner)
	{
		m_owner = Cast<AnxHero>(TryGetPawnOwner());
	}
	else
	{
		/// Hero velocity
		FVector velocity = m_owner->GetVelocity();
		velocity.Z = 0.f;
		heroVelocity = velocity.Size();

		// Basic condition for movement animation sequences
		if (!m_startedPlaying && heroVelocity != 0.f) m_startedPlaying = true;

		xReturn = m_owner->GetActorForwardVector().X;

		GEngine->AddOnScreenDebugMessage(0, GetWorld()->GetDeltaSeconds(), FColor::Cyan, FString::SanitizeFloat(xReturn));
		GEngine->AddOnScreenDebugMessage(1, GetWorld()->GetDeltaSeconds(), FColor::Cyan, FString::SanitizeFloat(velocity.X));
	}
}