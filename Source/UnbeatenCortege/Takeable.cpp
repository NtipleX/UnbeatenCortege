#include "Takeable.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"

ATakeable::ATakeable()
{
	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	meshComp->SetupAttachment(RootComponent);
	boxComp->SetupAttachment(meshComp);
	meshComp->SetRelativeLocation(FVector::ZeroVector);
	boxComp->SetRelativeLocation(FVector::ZeroVector);
	boxComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ATakeable::specificAction_Implementation()
{

}