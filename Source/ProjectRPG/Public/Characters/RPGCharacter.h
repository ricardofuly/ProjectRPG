// ₢ Copright Fuly Software Since 2025

#pragma once

#include "CoreMinimal.h"
#include "Characters/RPGCharacterBase.h"
#include "RPGCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
/**
 * 
 */
UCLASS()
class PROJECTRPG_API ARPGCharacter : public ARPGCharacterBase
{
	GENERATED_BODY()
public:
	ARPGCharacter();

	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> FollowCamera;

private:
	void InitAbilityActorInfo();
	
};
