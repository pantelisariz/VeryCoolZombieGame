// Copyright University of Inland Norway


#include "BTTask_FindRandomLocation.h"

#include "../CustomPawnBase.h"
#include "NavigationSystem.h"
#include "../PawnBase_AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_FindRandomLocation::UBTTask_FindRandomLocation(FObjectInitializer const& ObjectInitializer)
{
	NodeName = "Find Random Location In NavMesh";
}

EBTNodeResult::Type UBTTask_FindRandomLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	APawnBase_AIController* const AIControllerCast = Cast<APawnBase_AIController>( OwnerComp.GetAIOwner() );
	if (not AIControllerCast)
	{
		return EBTNodeResult::Failed;
	}
	// GEngine -> AddOnScreenDebugMessage(-1, 10.0f, FColor::Purple, FString::Printf(TEXT("Successfully casted to AIController")) );


	ACustomPawnBase* const PawnBaseCast = Cast<ACustomPawnBase>( AIControllerCast -> GetPawn() );
	if (not PawnBaseCast)
	{
		return EBTNodeResult::Failed;
	}
	// GEngine -> AddOnScreenDebugMessage(-1, 10.0f, FColor::Purple, FString::Printf(TEXT("Successfully casted to PawnBase")) );


	FVector const Origin = PawnBaseCast -> GetActorLocation();
	UNavigationSystemV1* const NavSys = UNavigationSystemV1::GetCurrent( GetWorld() );
	if (not NavSys)
	{
		return EBTNodeResult::Failed;
	}
	// GEngine -> AddOnScreenDebugMessage(-1, 10.0f, FColor::Purple, FString::Printf(TEXT("Successfully casted to NavMesh")) );

	/*
	 *Here the code actually starts. Everything over is just to make sure there's no nesting
	 */

	FNavLocation Location;
	if (NavSys -> GetRandomPointInNavigableRadius( Origin, SearchRadius, Location ))
	{
		OwnerComp.GetBlackboardComponent() -> SetValueAsVector( Out_RandomPointInNavMesh.SelectedKeyName, Location.Location );
	}

	// GEngine -> AddOnScreenDebugMessage(-1, 10.0f, FColor::Purple, FString::Printf(TEXT("Random Location: %f, %f"), Location.Location.X, Location.Location.Y) );


	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}
