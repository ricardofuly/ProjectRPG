// ₢ Copright Fuly Software Since 2025

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "RPGPlayerController.generated.h"

class IEnemyInterface;
struct FInputActionValue;
class UInputMappingContext;
class UInputAction;

UCLASS()
class PROJECTRPG_API ARPGPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ARPGPlayerController();

	virtual void PlayerTick(float DeltaTime) override;
	
protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

private:
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputMappingContext> InputMappingContext;

	UPROPERTY(EditAnywhere, Category = "Input|Movement")
	TObjectPtr<UInputAction> Move;

	UPROPERTY(EditAnywhere, Category = "Input|Movement")
	TObjectPtr<UInputAction> Look;

	UPROPERTY(EditAnywhere, Category = "Input|Movement")
	TObjectPtr<UInputAction> Jump;

	void OnMove(const FInputActionValue& InputActionValue);
	void OnLook(const FInputActionValue& InputActionValue);
	void OnJump();

	void EyesTrace();

	TScriptInterface<IEnemyInterface> LastActor;
	TScriptInterface<IEnemyInterface> ThisActor;
	
};


