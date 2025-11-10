// Copyright University of Inland Norway


#include "BTTask_FindHumanLocation.h"

UBTTask_FindHumanLocation::UBTTask_FindHumanLocation(FObjectInitializer const& ObjectInitializer)
{
	NodeName = "Find Location Of A Human";
}

EBTNodeResult::Type UBTTask_FindHumanLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	return Super::ExecuteTask(OwnerComp, NodeMemory);
}
