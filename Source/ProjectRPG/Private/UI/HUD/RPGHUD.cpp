// ₢ Copright Fuly Software Since 2025


#include "UI/HUD/RPGHUD.h"
#include "Blueprint/UserWidget.h"
#include "UI/Widget/RPGUserWidget.h"
#include "UI/WidgetController/OverlayWidgetController.h"

UOverlayWidgetController* ARPGHUD::GetOVerlayWidgetController(const FWidgetControllerParams& WidgetControllerParams)
{
	if (OverlayWidgetController == nullptr)
	{
		OverlayWidgetController = NewObject<UOverlayWidgetController>(this, OverlayWidgetControllerClass);
		OverlayWidgetController->SetWidgetControllerParams(WidgetControllerParams);

		return OverlayWidgetController;
	}
	return OverlayWidgetController;
}

void ARPGHUD::InitOverlay(APlayerController* PlayerController, APlayerState* PlayerState,
	UAbilitySystemComponent* AbilitySystemComponent, UAttributeSet* AttributeSet)
{
	checkf(OverlayWidgetClass, TEXT("Overlay Widget Class uninitialized, please fill out BP_AuraHUD"));
	checkf(OverlayWidgetControllerClass, TEXT("Overlay Widget Controller Class uninitialized, please fill out BP_AuraHUD"));
	
	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);
	OverlayWidget = Cast<URPGUserWidget>(Widget);

	const FWidgetControllerParams WidgetControllerParams(PlayerController, PlayerState, AbilitySystemComponent, AttributeSet);
	UOverlayWidgetController* WidgetController = GetOVerlayWidgetController(WidgetControllerParams);

	OverlayWidget->SetWidgetController(WidgetController);
	
	Widget->AddToViewport();
}
