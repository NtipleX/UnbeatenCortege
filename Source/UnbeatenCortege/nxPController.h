#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "nxPController.generated.h"

UCLASS()
class UNBEATENCORTEGE_API AnxPController : public APlayerController
{
	GENERATED_BODY()

public:
	AnxPController();

	UFUNCTION(BlueprintCallable)
	void MakeMouseCrosshair();
	UFUNCTION(BlueprintCallable)
	void MakeMouseCursor();

protected:
	// Setting up configuration for the game
	virtual void BeginPlay() override;
	virtual void Tick(float delta) override;
	// Process only LMB pressed
	virtual bool InputKey(FKey Key, EInputEvent EventType, float AmountDepressed, bool bGamepad) override;

private:
	void proceedFire();

private:
	/** CameraActor - scene's camera to set view to */
	UPROPERTY(EditDefaultsOnly, Category = nx, meta = (AllowPrivateAccess = "true"))
	class ACameraActor* CameraActor;

	/** CursorWidget - Crosshair widget */
	UPROPERTY(EditDefaultsOnly, Category = nx, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UUserWidget> CursorWidget;

	UPROPERTY(EditDefaultsOnly, Category = nx, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> CrossWidget;

	/// Misc
	class AnxHero* m_soldier;
	bool m_firing;
	UPROPERTY()
	UUserWidget* m_crosshair;
	UPROPERTY()
	UUserWidget* m_cursor;

};
