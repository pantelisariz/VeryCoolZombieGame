// Copyright University of Inland Norway

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Perception/AIPerceptionTypes.h"
#include "PawnBase_AIController.generated.h"

struct FAIStimulus;
/**
 * 
 */
UCLASS()
class ZOMBIEAPOCALYPSE_API APawnBase_AIController : public AAIController
{
	GENERATED_BODY()

public:
	explicit APawnBase_AIController(FObjectInitializer const& ObjectInitializer);

protected:
	virtual void OnPossess(APawn* InPawn) override;
private:
	UPROPERTY()
	class UAISenseConfig_Sight* SightConfig;
	
	virtual void SetupPerceptionSystem();

	virtual void OnTargetDetected(AActor* Actor , FAIStimulus const Stimulus);
};
