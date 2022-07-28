#include "nxPController.h"
#include "Camera/CameraActor.h"
#include "Kismet/GameplayStatics.h"
#include "TraceHelpers.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/PlayerInput.h"
#include "nxHero.h"

AnxPController::AnxPController() : m_firing(false)
{
	PrimaryActorTick.bCanEverTick = true;
}

void AnxPController::BeginPlay()
{
	/// Sets camera view to level's camera
	CameraActor = Cast<ACameraActor>(UGameplayStatics::GetActorOfClass(GetWorld(), ACameraActor::StaticClass()));
	if (CameraActor)
		SetViewTarget(CameraActor);
	else TRACE_WARNING(LogTemp, "Static actor camera not found on the scene");
	
	/// Mouse cursor crosshair
	SetShowMouseCursor(true);
	UUserWidget* crosshair = CreateWidget(this, CursorWidget, FName("CrosshairWidget"));
	if (crosshair)
		SetMouseCursorWidget(EMouseCursor::Default, crosshair);
	else TRACE_WARNING(LogTemp, "Crosshair hasn\'t been choosed in controller");
	bEnableClickEvents = true;

	m_soldier = Cast<AnxHero>(GetPawn());
	m_soldier->isEnemy = false;
}

void AnxPController::Tick(float delta)
{
	if (m_firing)
	{
		proceedFire();
	}

	/// Mouse deproject to world at click
	FVector WorldLocation, WorldDirection;
	DeprojectMousePositionToWorld(WorldLocation, WorldDirection);

	/// Line trace for mouse click
	FVector start, end;
	FHitResult hit;
	start = WorldLocation;
	end = WorldLocation + WorldDirection * 10000;
	FCollisionObjectQueryParams objParams(FCollisionObjectQueryParams::InitType::AllStaticObjects);
	if (GetWorld()->LineTraceSingleByObjectType(hit, start, end, objParams))
	{
		auto floor = hit.GetActor();
		if (floor)
		{
			//sDraw(hit.ImpactPoint);
			FVector2D A{ hit.ImpactPoint - m_soldier->GetActorLocation() };
			float sina = A.Y / A.Size();
			float angle = FMath::Acos(sina)*57.296 * -1*FMath::Sign(A.X);
			m_soldier->SetActorRotation(FRotator(0, angle+100, 0));

		}

	}
}

bool AnxPController::InputKey(FKey Key, EInputEvent EventType, float AmountDepressed, bool bGamepad)
{
	if (Key.GetFName() == "LeftMouseButton" && EventType == EInputEvent::IE_Pressed)
	{
		m_firing = true;
	}
	else if(Key.GetFName() == "LeftMouseButton" && EventType == EInputEvent::IE_Released)
		m_firing = false;
	return Super::InputKey(Key, EventType, AmountDepressed, bGamepad);
}

void AnxPController::proceedFire()
{
	/// Mouse deproject to world at click
	FVector WorldLocation, WorldDirection;
	DeprojectMousePositionToWorld(WorldLocation, WorldDirection);

	/// Line trace for mouse click
	FVector start, end;
	FHitResult hit;
	start = WorldLocation;
	end = WorldLocation + WorldDirection * 10000;
	end.X -= 100;
	FCollisionObjectQueryParams objParams(FCollisionObjectQueryParams::InitType::AllStaticObjects);
	if (GetWorld()->LineTraceSingleByObjectType(hit, start, end, objParams))
	{
		auto floor = hit.GetActor();
		if (floor)
		{
			//sDraw(hit.ImpactPoint);
			m_soldier->fireWeapon(hit.ImpactPoint);
		}

	}
}