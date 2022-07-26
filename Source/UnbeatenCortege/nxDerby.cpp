#include "nxDerby.h"
#include "Components/StaticMeshComponent.h"

AnxDerby::AnxDerby() : debryStrenght(0.f)
{
	debryMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("debryMesh"));
	RootComponent = debryMesh;
	debryMesh->SetWorldScale3D(FVector(0.1, 0.1, 0.1));

	PrimaryActorTick.bCanEverTick = true;
	debryMesh->SetSimulatePhysics(true);
	debryMesh->SetEnableGravity(true);
	debryMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	debryMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	debryMesh->SetCollisionObjectType(ECollisionChannel::ECC_Visibility);
	debryMesh->SetMassScale(FName(), 0.f);
}

void AnxDerby::BeginPlay()
{
	Super::BeginPlay();
	
}

void AnxDerby::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	debryMesh->AddForce(FVector(0,0,debryStrenght));
}

