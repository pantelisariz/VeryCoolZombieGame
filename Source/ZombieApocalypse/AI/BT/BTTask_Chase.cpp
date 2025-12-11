// Copyright University of Inland Norway


#include "BTTask_Chase.h"

#include "../PawnBase_AIController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

UBTTask_Chase::UBTTask_Chase(FObjectInitializer const& ObjectInitializer)
{
	NodeName = TEXT("Chase Target");
}

EBTNodeResult::Type UBTTask_Chase::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	
	auto* const AIController = Cast<APawnBase_AIController>(OwnerComp.GetAIOwner());
	if (not AIController)
	{
		return EBTNodeResult::Failed;
	}
	
	auto const TargetLocation = OwnerComp.GetBlackboardComponent() -> GetValueAsVector(In_TargetLocation.SelectedKeyName);
	
	UAIBlueprintHelperLibrary::SimpleMoveToLocation(AIController, TargetLocation);
	
	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}
