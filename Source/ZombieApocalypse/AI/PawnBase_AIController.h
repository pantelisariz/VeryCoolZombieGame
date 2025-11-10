// Copyright University of Inland Norway

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AIPerceptionComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
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
	UPROPERTY()
	UAISenseConfig_Sight* SightConfig;

protected:
	virtual void OnPossess(APawn* InPawn) override;
	
private:
	virtual void SetupPerceptionSystem();

	virtual void OnTargetDetected(AActor* Actor , FAIStimulus const Stimulus);


};
