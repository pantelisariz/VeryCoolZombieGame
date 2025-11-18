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
	
	
	//UE_LOG(LogTemp, Warning, TEXT("Change speed"));
	
	
	auto const AIController = OwnerComp.GetAIOwner();
	if (not AIController)
	{
		// UE_LOG(LogTemp, Warning, TEXT("Cant get Ownercomp"));
		return;
	}
	
	auto* const PawnBase = Cast<ACustomPawnBase>(AIController -> GetPawn());
	if (not PawnBase)
	{
		// UE_LOG(LogTemp, Warning, TEXT("Cant cast to PawnBase"));
		return;
	}
	
	
	if (bUseRunInsteadOfWalk)
	{
		// UE_LOG(LogTemp, Warning, TEXT("Use Run Instead Of Walk"));
		PawnBase -> FloatingPawnMovementComponent -> MaxSpeed = PawnBase -> MaxRunSpeed;
	}
	else
	{
		// UE_LOG(LogTemp, Warning, TEXT("Don't Use Run Instead Of Walk"));
		PawnBase -> FloatingPawnMovementComponent -> MaxSpeed = PawnBase -> MaxWalkSpeed;
	}
}
