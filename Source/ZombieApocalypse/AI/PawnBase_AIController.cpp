// Copyright University of Inland Norway


#include "PawnBase_AIController.h"
#include "CustomPawnBase.h"

APawnBase_AIController::APawnBase_AIController(FObjectInitializer const& ObjectInitializer)
{
}

void APawnBase_AIController::OnPossess(APawn* InPawn)
{
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

	/*
	UBlackboardComponent* BlackBoardComponent;
	UseBlackboard(BehaviorTreeCast -> BlackboardAsset, BlackBoardComponent);
	Blackboard = BlackBoardComponent;
	RunBehaviorTree(BehaviorTreeCast);
	*/
}

void APawnBase_AIController::SetupPerceptionSystem()
{
}

void APawnBase_AIController::OnTargetDetected(AActor* Actor, FAIStimulus const Stimulus)
{
}
