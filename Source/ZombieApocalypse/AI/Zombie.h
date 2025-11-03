// Copyright University of Inland Norway

#pragma once

#include "CoreMinimal.h"
#include "CustomPawnBase.h"
#include "GameFramework/Pawn.h"
#include "ZombieApocalypse/PopulationSpawner.h"
#include "Zombie.generated.h"

UCLASS()
class ZOMBIEAPOCALYPSE_API AZombie : public ACustomPawnBase
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AZombie();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	virtual void Interact(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	APopulationSpawner* PopulationSpawner;

};