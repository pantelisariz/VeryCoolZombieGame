// Copyright University of Inland Norway

#pragma once

#include "CoreMinimal.h"
#include "../CustomPawnBase.h"
#include "GameFramework/Pawn.h"
#include "Zombie.generated.h"

class AHuman;
class ABitten;

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

	/** Bitten actor to spawn (set in editor or BP) */
	UPROPERTY(EditDefaultsOnly, Category = "Bite")
	TSubclassOf<ABitten> BittenClass;

	/** Cooldown between bites so a single overlap can't convert repeatedly */
	UPROPERTY(EditDefaultsOnly, Category = "Bite")
	float BiteCooldown;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	virtual void Interact(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit) override;

private:
	float LastBiteTime;

	UFUNCTION()
	void OnSphereBeginOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);

	/** Core logic to convert a human to bitten on server */
	void TryConvertHuman(AHuman* Human);



};