// Copyright University of Inland Norway


#include "UBTService_ChangeSpeed.h"

#include "CustomPawnBase.h"

UUBTService_ChangeSpeed::UUBTService_ChangeSpeed()
{
	bNotifyBecomeRelevant = true;
	NodeName = TEXT("Change Speed");
	bUseRunInsteadOfWalk = false;
}

void UUBTService_ChangeSpeed::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::OnBecomeRelevant(OwnerComp, NodeMemory);
	
	
	auto const AIController = OwnerComp.GetAIOwner();
	if (AIController)
	{
		return;
	}
	
	auto* const PawnBase = Cast<ACustomPawnBase>(AIController -> GetPawn());
	if (not PawnBase)
	{
		return;
	}
	
	
	if (bUseRunInsteadOfWalk)
	{
		PawnBase -> FloatingPawnMovementComponent -> MaxSpeed = PawnBase -> MaxRunSpeed;
	}
	else
	{
		PawnBase -> FloatingPawnMovementComponent -> MaxSpeed = PawnBase -> MaxWalkSpeed;
	}
}
