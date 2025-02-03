// ₢ Copright Fuly Software Since 2025


#include "Characters/RPGCharacter.h"

#include "AbilitySystemComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "PlayerState/RPGPlayerState.h"

ARPGCharacter::ARPGCharacter()
{
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>("Camera Boom");
	CameraBoom->SetupAttachment(RootComponent);
	FollowCamera = CreateDefaultSubobject<UCameraComponent>("Follow Camera");
	FollowCamera->SetupAttachment(CameraBoom);
}

void ARPGCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	InitAbilityActorInfo();
}

void ARPGCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	InitAbilityActorInfo();
}

void ARPGCharacter::InitAbilityActorInfo()
{
	if (ARPGPlayerState* RPGPlayerState = GetPlayerState<ARPGPlayerState>())
	{
		RPGPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(RPGPlayerState, this);
		AbilitySystemComponent = RPGPlayerState->GetAbilitySystemComponent();
		AttributeSet = RPGPlayerState->GetAttributeSet();
	}
}
