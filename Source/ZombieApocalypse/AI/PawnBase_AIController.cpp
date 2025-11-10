// Copyright University of Inland Norway


#include "PawnBase_AIController.h"
#include "CustomPawnBase.h"


void APawnBase_AIController::OnPossess(APawn* InPawn)
{
	GEngine -> AddOnScreenDebugMessage(-1, 10.0f, FColor::Purple, FString::Printf(TEXT("On Possessed")) );
	Super::OnPossess(InPawn);


	ACustomPawnBase* const CustomPawnBaseCast = Cast<ACustomPawnBase>(InPawn);
	if (not CustomPawnBaseCast)
	{
		return;
	}

	UBehaviorTree* const BehaviorTreeCast = CustomPawnBaseCast -> BehaviorTree;
	if (not BehaviorTreeCast)
	{
		return;
	}

	
	UBlackboardComponent* BlackBoardComponent;
	UseBlackboard(BehaviorTreeCast -> BlackboardAsset, BlackBoardComponent);
	Blackboard = BlackBoardComponent;
	RunBehaviorTree(BehaviorTreeCast);

	GEngine -> AddOnScreenDebugMessage(-1, 10.0f, FColor::Purple, FString::Printf(TEXT("Possessed")) );

	
}

void APawnBase_AIController::SetupPerceptionSystem()
{
}

void APawnBase_AIController::OnTargetDetected(AActor* Actor, FAIStimulus const Stimulus)
{
}
