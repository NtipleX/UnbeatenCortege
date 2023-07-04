#include "nxWeapon.h"
#include "Components/StaticMeshComponent.h"
#include "nxHero.h"
#include "nxProjectile.h"
#include "Sound/SoundCue.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "Kismet/KismetMathLibrary.h"
#include "nxPController.h"
#include "nxGameMode.h"

AnxWeapon::AnxWeapon() : reloadTime(1.f), m_ammoFired(0)
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
	auto GM = dynamic_cast<AnxGameMode*>(UGameplayStatics::GetGameMode(GetWorld()));
	GM->OnGameStarted.AddDynamic(this, &AnxWeapon::OnGameStarted);
	
}

void AnxWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool AnxWeapon::fireWeapon(FVector direction, FVector startPos)
{
	if(GetWorldTimerManager().GetTimerRemaining(m_timer_reload)>0.1) return false;
	
	GetWorldTimerManager().SetTimer(m_timer_reload, reloadTime, false, reloadTime);
	/// Shoot by direction
	FVector start = startPos;//GetActorLocation();
	start.Z -= 10;
	//lDraw(start, start + direction);
	if (projectile)
	{
		UGameplayStatics::PlaySound2D(GetWorld(), SoundFire);
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ParticleFire, GetActorLocation());
		FVector2D A1{ start + direction };
		A1 -= FVector2D{ startPos };
		float sina = A1.Y / A1.Size();
		auto degrees = FMath::Acos(sina) * 57.296 * -1*FMath::Sign(A1.X);
		FRotator rot(0, degrees, 0 );

		rot.Yaw += UKismetMathLibrary::RandomFloatInRange(MinSpread, MaxSpread);
		auto pushed = GetWorld()->SpawnActor<AnxProjectile>(projectile, start, rot);
		m_ammoFired++;
		if (m_ammoFired >= 18 && AmmoMag)
		{
			m_ammoFired = 0;
			GetWorld()->SpawnActor<AActor>(AmmoMag, GetActorLocation(), GetActorRotation());
		}
		if (FMath::RandBool())
		{
			GetWorld()->SpawnActor<AActor>(AmmoEmptis, GetActorLocation(), GetActorRotation());
		}
	}
	else TRACE_WARNING(LogTemp, "Projectile for weapon not set");
	return true;
}

void AnxWeapon::OnGameStarted()
{
	auto con = dynamic_cast<AnxPController*>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (con && con->AdaptiveCompressor)
	{
		reloadTime *= 0.8;
	}
}