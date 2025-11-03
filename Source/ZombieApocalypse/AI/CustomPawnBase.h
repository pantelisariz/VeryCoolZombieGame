// Copyright University of Inland Norway

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Pawn.h"
#include "CustomPawnBase.generated.h"

UCLASS()
class ZOMBIEAPOCALYPSE_API  ACustomPawnBase: public APawn
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (MakeEditWidget = "true", AllowPrivateAccess = "true"))
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (MakeEditWidget = "true", AllowPrivateAccess = "true"))
	USphereComponent* SphereCollider;
	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (MakeEditWidget = "true", AllowPrivateAccess = "true"))
	double maxSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (MakeEditWidget = "true", AllowPrivateAccess = "true"))
	int health;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (MakeEditWidget = "true", AllowPrivateAccess = "true"))
	TSubclassOf<AAIController> PawnAIController;

	virtual void Interact();

};
