#include "nxWeapon.h"
#include "Components/StaticMeshComponent.h"
#include "nxHero.h"
#include "nxProjectile.h"

AnxWeapon::AnxWeapon() : reloadTime(1.f)
{
	weaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("weaponMeshComp"));
	weaponMesh->SetupAttachment(RootComponent);
	weaponMesh->SetRelativeLocation(FVector::ZeroVector);
	weaponMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	weaponMesh->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	weaponMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	weaponMesh->SetGenerateOverlapEvents(false);

	PrimaryActorTick.bCanEverTick = false;

}

void AnxWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

void AnxWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AnxWeapon::fireWeapon(FVector direction)
{
	if(GetWorldTimerManager().GetTimerRemaining(m_timer_reload)>0.1) return;
	
	GetWorldTimerManager().SetTimer(m_timer_reload, reloadTime, false, reloadTime);
	/// Shoot by direction
	FVector start = GetActorLocation();
	start.Z -= 20;
	//lDraw(start, start + direction);
	if (projectile)
	{
		FVector2D A1{ start + direction };
		A1 -= FVector2D{ GetActorLocation() };
		float sina = A1.Y / A1.Size();
		auto degrees = FMath::Acos(sina) * 57.296 * -1*FMath::Sign(A1.X);
		FRotator rot(0, degrees, 0 );

		auto pushed = GetWorld()->SpawnActor<AnxProjectile>(projectile, start, rot);
	}
	else TRACE_WARNING(LogTemp, "Projectile for weapon not set");
}