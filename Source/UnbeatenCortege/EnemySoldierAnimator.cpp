#include "EnemySoldierAnimator.h"
#include "EnemySoldier.h"

void UEnemySoldierAnimator::NativeUpdateAnimation(float delta)
{
	Super::NativeUpdateAnimation(delta);
	if(Owner)
	{
		FVector2D velocity{Owner->GetVelocity()};
		IsMoving = velocity.Size() != 0.f ? true : false;
	}
}

void UEnemySoldierAnimator::NativeBeginPlay()
{
	Super::NativeBeginPlay();
	Owner = dynamic_cast<AEnemySoldier*>(TryGetPawnOwner());

}

