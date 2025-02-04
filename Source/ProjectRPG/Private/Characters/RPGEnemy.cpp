// ₢ Copright Fuly Software Since 2025


#include "Characters/RPGEnemy.h"

#include "AbilitySystem/RPGAbilitySystemComponent.h"
#include "AttributeSet/RPGAttributeSet.h"
#include "Kismet/KismetSystemLibrary.h"
#include "ProjectRPG/ProjectRPG.h"

ARPGEnemy::ARPGEnemy()
{
	AbilitySystemComponent = CreateDefaultSubobject<URPGAbilitySystemComponent>("Ability System Component");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	AttributeSet = CreateDefaultSubobject<URPGAttributeSet>("Attribute Set");
}

void ARPGEnemy::HighlightActor()
{
	UKismetSystemLibrary::DrawDebugSphere(GetWorld(), GetActorLocation(),100.f,12, FColor::Red, 0.5f, 1);
	GetMesh()->SetRenderCustomDepth(true);
	GetMesh()->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
	Weapon->SetRenderCustomDepth(true);
	Weapon->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
}

void ARPGEnemy::UnHighlightActor()
{
	GetMesh()->SetRenderCustomDepth(false);
	Weapon->SetRenderCustomDepth(false);
}

void ARPGEnemy::BeginPlay()
{
	Super::BeginPlay();

	AbilitySystemComponent->InitAbilityActorInfo(this, this);
}
