// Copyright University of Inland Norway

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_FindHumanLocation.generated.h"

/**
 * 
 */
UCLASS()
class ZOMBIEAPOCALYPSE_API UBTTask_FindHumanLocation : public UBTTaskNode
{
	GENERATED_BODY()

public:
	explicit UBTTask_FindHumanLocation(FObjectInitializer const& ObjectInitializer);
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	
	UPROPERTY(EditAnywhere, Category = "Blackboard", meta = (AllowPrivateAccess = "true"))
	FBlackboardKeySelector RandomPointInNavMesh;
	
};
