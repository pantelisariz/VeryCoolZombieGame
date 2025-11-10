// Copyright University of Inland Norway

#pragma once

#include "CoreMinimal.h"
#include "../CustomPawnBase.h"
#include "GameFramework/Pawn.h"
#include "Human.generated.h"

UCLASS()
class ZOMBIEAPOCALYPSE_API AHuman : public ACustomPawnBase
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AHuman();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
