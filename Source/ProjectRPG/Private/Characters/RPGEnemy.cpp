// ₢ Copright Fuly Software Since 2025


#include "Characters/RPGEnemy.h"
#include "Kismet/KismetSystemLibrary.h"
#include "ProjectRPG/ProjectRPG.h"

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
