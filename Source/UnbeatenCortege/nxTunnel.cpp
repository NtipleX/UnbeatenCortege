#include "nxTunnel.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ChildActorComponent.h"
#include "GameFramework/Character.h"
#include "TraceHelpers.h"



// Sets default values
AnxTunnel::AnxTunnel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	arcMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("arcMesh"));
	innerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("innerMesh"));
	arcMesh->SetupAttachment(RootComponent);
	innerMesh->SetupAttachment(arcMesh);
	arcMesh->SetRelativeLocation(FVector::ZeroVector);
	innerMesh->SetRelativeLocation(FVector::ZeroVector);
	spawnLoc = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Location"));
	spawnLoc->SetupAttachment(arcMesh);
	spawnLoc->SetRelativeLocation(FVector::ZeroVector);
	spawnLoc->SetRelativeLocation(FVector::ZeroVector);
	spawnLoc->SetHiddenInGame(true);

	arcMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	arcMesh->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	innerMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	innerMesh->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	arcMesh->SetCanEverAffectNavigation(false);
	innerMesh->SetCanEverAffectNavigation(false);

}

AActor* AnxTunnel::spawnUnit(TSubclassOf<ACharacter> unitClass)
{
	FActorSpawnParameters params;
	params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	return GetWorld()->SpawnActor<ACharacter>(unitClass.Get(), GetActorLocation(), GetActorRotation()-FRotator(0,90,0), params);
}

// Called when the game starts or when spawned
void AnxTunnel::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AnxTunnel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

