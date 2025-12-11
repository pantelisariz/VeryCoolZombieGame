// Copyright University of Inland Norway

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Components/SphereComponent.h"
#include "PawnBase_AIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "GameFramework/Character.h"
#include "CustomPawnBase.generated.h"

UCLASS()
class ZOMBIEAPOCALYPSE_API  ACustomPawnBase: public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACustomPawnBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	//	+++ PAST THIS POINT OUR IMPLEMENTATION STARTS +++
	virtual void Interact(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit);

	
	void TakeDamage(float Damage, bool bDamagerWasMelee = false);
	void MakeWeak();
	void MakeNormal();

	AController* WeakController;
	FTimerHandle TimerHandle_Weak;
	

	
	
/*
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (MakeEditWidget = "true", AllowPrivateAccess = "true"))
	USkeletalMeshComponent* Mesh;
	*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PawnBase", meta = (MakeEditWidget = "true", AllowPrivateAccess = "true"))
	USphereComponent* SphereCollider;

	/*
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (MakeEditWidget = "true", AllowPrivateAccess = "true"))
	UFloatingPawnMovement* FloatingPawnMovementComponent;
	*/
	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PawnBase|Stats", meta = (MakeEditWidget = "true", AllowPrivateAccess = "true"))
	double MaxWalkSpeed;	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PawnBase|Stats", meta = (MakeEditWidget = "true", AllowPrivateAccess = "true"))
	double MaxRunSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PawnBase|Stats", meta = (MakeEditWidget = "true", AllowPrivateAccess = "true"))
	int32 Health;	
	
	// Basically money gained from killing zombies or lost when killing humans
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PawnBase|Stats", meta = (MakeEditWidget = "true", AllowPrivateAccess = "true"))
	int32 CashChangeValue;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PawnBase|Stats", meta = (MakeEditWidget = "true", AllowPrivateAccess = "true"))
	int32 HealthToBecomeWeakValue;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PawnBase|Stats", meta = (MakeEditWidget = "true", AllowPrivateAccess = "true"))
	float WeaknessLenght;
	bool bIsWeakened;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PawnBase", meta = (MakeEditWidget = "true", AllowPrivateAccess = "true"))
	UMaterialInterface* MaterialWithHighlight;

	
	
	
	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	UBehaviorTree*  BehaviorTree;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (MakeEditWidget = "true", AllowPrivateAccess = "true"))
	TSubclassOf<APawnBase_AIController> PawnAIController;


	

};
