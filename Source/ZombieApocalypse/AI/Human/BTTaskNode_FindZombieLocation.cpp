// Copyright University of Inland Norway


#include "BTTaskNode_FindZombieLocation.h"

#include "NavigationSystem.h"
#include "Kismet/GameplayStatics.h"
#include "ZombieApocalypse/AI/Zombie/Zombie.h"

UBTTaskNode_FindZombieLocation::UBTTaskNode_FindZombieLocation(FObjectInitializer const& ObjectInitializer)
{
	NodeName = "Find Location Of Zombie";
}

EBTNodeResult::Type UBTTaskNode_FindZombieLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto bob = OwnerComp.GetBlackboardComponent()->GetValueAsObject(In_ZombieActor.SelectedKeyName);

	AZombie* const HumanCast = Cast<AZombie>(bob);
	if (not HumanCast)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Purple, FString::Printf(TEXT("Failed cast to AHuman")));
		return EBTNodeResult::Failed;
	}

	FVector const ZombieCastLocation = HumanCast->GetActorLocation();
	if (not bSearchRandom)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(Out_ZombieTargetLocation.SelectedKeyName, ZombieCastLocation);

		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		return EBTNodeResult::Succeeded;
	}

	FNavLocation Location;
	UNavigationSystemV1* const Navsys = UNavigationSystemV1::GetCurrent(GetWorld());
	if (not Navsys)
	{
		return EBTNodeResult::Failed;
	}

	if (Navsys->GetRandomPointInNavigableRadius(ZombieCastLocation, SearchRadius, Location))
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(Out_ZombieTargetLocation.SelectedKeyName, Location.Location);
	}

	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Purple, FString::Printf(TEXT("Found AHuman")));

	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}
