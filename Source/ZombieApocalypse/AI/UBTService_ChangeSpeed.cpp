// Copyright University of Inland Norway


#include "UBTService_ChangeSpeed.h"

#include "CustomPawnBase.h"

UUBTService_ChangeSpeed::UUBTService_ChangeSpeed()
{
	bNotifyBecomeRelevant = true;
	NodeName = TEXT("Change Speed");
	Speed = 600;
}

void UUBTService_ChangeSpeed::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::OnBecomeRelevant(OwnerComp, NodeMemory);
	if (auto const AIController = OwnerComp.GetAIOwner())
	{
		if (auto* const PawnBase = Cast<ACustomPawnBase>(AIController -> GetPawn()))
		{
			PawnBase -> FloatingPawnMovementComponent -> MaxSpeed = Speed;
		}
	}
}
