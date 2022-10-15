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
		xHeroVelocity = m_owner->xLook* velocity.X;
		yHeroVelocity = m_owner->yLook* velocity.Y;

		// Basic condition for movement animation sequences
		if (!m_startedPlaying && heroVelocity != 0.f) m_startedPlaying = true;

		xReturn = m_owner->GetActorForwardVector().X;
		yReturn = m_owner->GetActorRightVector().Y;
		xVelocity = velocity.X / 125 * FMath::Sign(velocity.X);
	}
}