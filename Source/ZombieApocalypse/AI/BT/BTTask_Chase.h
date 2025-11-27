// Copyright University of Inland Norway

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_Chase.generated.h"

/**
 * 
 */
UCLASS()
class ZOMBIEAPOCALYPSE_API UBTTask_Chase : public UBTTaskNode
{
	GENERATED_BODY()
public:	
	explicit UBTTask_Chase(FObjectInitializer const& ObjectInitializer);
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackboard", meta = (AllowPrivateAccess = "true"))
	FBlackboardKeySelector In_TargetLocation;

};
