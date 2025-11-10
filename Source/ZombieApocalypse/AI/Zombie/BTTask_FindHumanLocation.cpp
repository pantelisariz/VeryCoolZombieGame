// Copyright University of Inland Norway


#include "BTTask_FindHumanLocation.h"

#include "NavigationSystem.h"
#include "Kismet/GameplayStatics.h"
#include "ZombieApocalypse/AI/Human/Human.h"

UBTTask_FindHumanLocation::UBTTask_FindHumanLocation(FObjectInitializer const& ObjectInitializer)
{
	NodeName = "Find Location Of A Human";
}

EBTNodeResult::Type UBTTask_FindHumanLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto bob = OwnerComp.GetBlackboardComponent() -> GetValueAsObject(In_HumanActor.SelectedKeyName);

	AHuman* const HumanCast = Cast<AHuman>(bob);
	if (not HumanCast)
	{
		GEngine -> AddOnScreenDebugMessage(-1, 1.0f, FColor::Purple, FString::Printf(TEXT("Failed cast to AHuman")) );
		return EBTNodeResult::Failed;
	}

	FVector const HumanCastLocation = HumanCast -> GetActorLocation();
	if (not bSearchRandom)
	{
		OwnerComp.GetBlackboardComponent() -> SetValueAsVector(Out_HumanTargetLocation.SelectedKeyName, HumanCastLocation);

		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		return EBTNodeResult::Succeeded;
	}

	FNavLocation Location;
	UNavigationSystemV1* const Navsys = UNavigationSystemV1::GetCurrent(GetWorld());
	if (not Navsys)
	{
		return EBTNodeResult::Failed;
	}

	if ( Navsys -> GetRandomPointInNavigableRadius(HumanCastLocation, SearchRadius, Location) )
	{
		OwnerComp.GetBlackboardComponent() -> SetValueAsVector(Out_HumanTargetLocation.SelectedKeyName, Location.Location);
	}
	
	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}
