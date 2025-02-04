// ₢ Copright Fuly Software Since 2025


#include "Characters/RPGCharacter.h"

#include "AbilitySystemComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "PlayerController/RPGPlayerController.h"
#include "PlayerState/RPGPlayerState.h"
#include "UI/HUD/RPGHUD.h"

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
	ARPGPlayerState* RPGPlayerState = GetPlayerState<ARPGPlayerState>();
	check(RPGPlayerState);
	RPGPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(RPGPlayerState, this);
	AbilitySystemComponent = RPGPlayerState->GetAbilitySystemComponent();
	AttributeSet = RPGPlayerState->GetAttributeSet();

	if (ARPGPlayerController* RPGPlayerController = Cast<ARPGPlayerController>(GetController()))
	{
		if (ARPGHUD* RPGHUD = Cast<ARPGHUD>(RPGPlayerController->GetHUD()))
		{
			RPGHUD->InitOverlay(RPGPlayerController, RPGPlayerState, AbilitySystemComponent, AttributeSet);
		}
	}
}
