#include "nxProjectile.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "TraceHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "nxHero.h"
#include "MetalBarricade.h"
#include "Sound/SoundCue.h"
#include "EnemySoldier.h"
#include "nxStructure.h"

AnxProjectile::AnxProjectile() : damage(10.f)
{
	/// Creation
	projMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("projMeshComp"));
	projParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("projParticleComp"));
	projMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("projMoveComp"));
	projBox = CreateDefaultSubobject<UBoxComponent>(TEXT("projBoxComp"));
	projRoot = CreateDefaultSubobject<USceneComponent>(TEXT("projRootComp"));

	/// Attachment
	RootComponent = projRoot;
	projMesh->SetupAttachment(RootComponent);
	projBox->SetupAttachment(RootComponent);
	projParticle->SetupAttachment(RootComponent);
	
	/// Position
	projRoot->SetRelativeLocation(FVector::ZeroVector);
	projBox->SetRelativeLocation(FVector::ZeroVector);
	projMesh->SetRelativeLocation(FVector::ZeroVector);
	projParticle->SetRelativeLocation(FVector::ZeroVector);

	/// Configuration
	PrimaryActorTick.bCanEverTick = false;
	projMesh->SetSimulatePhysics(false);
	projMesh->SetEnableGravity(false);
	projMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	projMesh->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	projMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	projBox->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	projBox->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	projBox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	projBox->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldStatic, ECollisionResponse::ECR_Overlap);
	projBox->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	projBox->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldDynamic, ECollisionResponse::ECR_Overlap);
	FScriptDelegate deleg;
	deleg.BindUFunction(this, "projectileHit");
	projBox->OnComponentBeginOverlap.Add(deleg);
}

void AnxProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

void AnxProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AnxProjectile::projectileHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IsPendingKill() || OtherActor->ActorHasTag(FName("Invisible")))
		return;

	
	auto unit = Cast<AnxHero>(OtherActor);
	auto enemy = Cast<AEnemySoldier>(OtherActor);
	if(unit && unit->isEnemy || Cast<UWall>(OtherComp) && !Cast<AMetalBarricade>(OtherActor))
	{
		if (Cast<UWall>(OtherComp))
		{
			OtherActor->TakeDamage(damage, FDamageEvent(), UGameplayStatics::GetPlayerController(GetWorld(), 0), this);
			Cast<UWall>(OtherComp)->GetDamage();
		}
		else
			UGameplayStatics::SpawnSound2D(GetWorld(), SoundNormalHit3);
		OtherActor->TakeDamage(damage, FDamageEvent(), UGameplayStatics::GetPlayerController(GetWorld(), 0), this);
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), explosion, GetActorLocation());
		projMesh->SetHiddenInGame(true);
		projParticle->DeactivateSystem();
		MarkPendingKill();
	}
	else if (enemy)
	{
		OtherActor->TakeDamage(damage, FDamageEvent(), UGameplayStatics::GetPlayerController(GetWorld(), 0), this);
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), explosion, GetActorLocation());
		UGameplayStatics::SpawnSound2D(GetWorld(), SoundNormalHit3);
		projMesh->SetHiddenInGame(true);
		projParticle->DeactivateSystem();
		MarkPendingKill();
	}
	else if (Cast<AnxStructure>(OtherActor))
	{
		OtherActor->TakeDamage(damage, FDamageEvent(), UGameplayStatics::GetPlayerController(GetWorld(), 0), this);
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), explosion, GetActorLocation());
		UGameplayStatics::SpawnSound2D(GetWorld(), SoundNormalHit3);
		UGameplayStatics::SpawnSound2D(GetWorld(), SoundNormalHit2);
		UGameplayStatics::SpawnSound2D(GetWorld(), SoundNormalHit);
		projMesh->SetHiddenInGame(true);
		projParticle->DeactivateSystem();
		MarkPendingKill();
	}
	else
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), explosion, GetActorLocation());
		UGameplayStatics::SpawnSound2D(GetWorld(), SoundNormalHit2);
		UGameplayStatics::SpawnSound2D(GetWorld(), SoundNormalHit);
		projMesh->SetHiddenInGame(true);
		projParticle->DeactivateSystem();
		MarkPendingKill();
	}
}

