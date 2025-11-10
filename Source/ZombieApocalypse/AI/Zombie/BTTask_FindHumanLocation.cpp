// Copyright University of Inland Norway


#include "BTTask_FindHumanLocation.h"

#include "Kismet/GameplayStatics.h"
#include "ZombieApocalypse/AI/Human/Human.h"

UBTTask_FindHumanLocation::UBTTask_FindHumanLocation(FObjectInitializer const& ObjectInitializer)
{
	NodeName = "Find Location Of A Human";
}

EBTNodeResult::Type UBTTask_FindHumanLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AHuman* const HumanCast = Cast<AHuman>(
	OwnerComp.GetBlackboardComponent() -> GetValueAsObject(HumanActor.SelectedKeyName) );
	if (not HumanCast)
	{
		return EBTNodeResult::Failed;
	}
	
	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}
