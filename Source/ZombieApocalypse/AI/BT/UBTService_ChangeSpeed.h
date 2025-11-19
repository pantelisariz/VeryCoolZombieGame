// Copyright University of Inland Norway

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "UBTService_ChangeSpeed.generated.h"

/**
 * 
 */
UCLASS()
class ZOMBIEAPOCALYPSE_API UUBTService_ChangeSpeed : public UBTService
{
	GENERATED_BODY()
	
protected:
	UUBTService_ChangeSpeed();
	virtual void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	bool bUseRunInsteadOfWalk;
};
