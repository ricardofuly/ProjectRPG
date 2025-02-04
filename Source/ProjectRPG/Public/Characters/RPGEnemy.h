// ₢ Copright Fuly Software Since 2025

#pragma once

#include "CoreMinimal.h"
#include "Characters/RPGCharacterBase.h"
#include "Interfaces/EnemyInterface.h"
#include "RPGEnemy.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTRPG_API ARPGEnemy : public ARPGCharacterBase, public IEnemyInterface
{
	GENERATED_BODY()
	ARPGEnemy();

public:
	virtual void HighlightActor() override;
	virtual void UnHighlightActor() override;

protected:
	virtual void BeginPlay() override;
};
