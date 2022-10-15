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

			// Determine x/y look.
			if (m_soldier)
			{
				FVector heroLoc = m_soldier->GetActorLocation();
				FVector cursorLoc = hit.ImpactPoint;
				m_soldier->xLook = heroLoc.X< cursorLoc.X ? 1 : -1;
				m_soldier->yLook = heroLoc.Y< cursorLoc.Y ? 1 : -1;
			}
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
	//end.X -= 100;
	FCollisionObjectQueryParams objParams(FCollisionObjectQueryParams::InitType::AllObjects);
	if(GetWorld()->LineTraceSingleByObjectType(hit, start, end, objParams))
	{
		if(dynamic_cast<ACharacter*>(hit.Actor.Get()))
		{
			m_soldier->fireWeapon(hit.Actor->GetActorLocation()-FVector(0, 0, 25));
		}
		else
		{
			FCollisionObjectQueryParams objParams2(FCollisionObjectQueryParams::InitType::AllStaticObjects);
			GetWorld()->LineTraceSingleByObjectType(hit, start, end, objParams2);
			m_soldier->fireWeapon(hit.ImpactPoint);
		}
	}
}