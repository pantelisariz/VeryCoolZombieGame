// Copyright University of Inland Norway

#pragma once

#include "CoreMinimal.h"
#include "../PawnBase_AIController.h"
#include "Zombie_AIController.generated.h"

/**
 * 
 */
UCLASS()
class ZOMBIEAPOCALYPSE_API AZombie_AIController : public APawnBase_AIController
{
	GENERATED_BODY()

	
public:
	explicit AZombie_AIController(FObjectInitializer const& ObjectInitializer);

protected:
	virtual void OnPossess(APawn* InPawn) override;

private:
	
	virtual void SetupPerceptionSystem() override;

	UFUNCTION()
	virtual void OnTargetDetected(AActor* Actor , FAIStimulus const Stimulus) override;
	
};
