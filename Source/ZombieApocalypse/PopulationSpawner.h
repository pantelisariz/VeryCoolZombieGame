// Copyright University of Inland Norway

#pragma once

#include "CoreMinimal.h"
#include "Engine/TargetPoint.h"
#include "GameFramework/Actor.h"
#include "AI/Zombie//Zombie.h"
#include "AI/Human//Human.h"
#include "AI/Bitten//Bitten.h"
#include "HUD/CounterHUD.h"
#include "PopulationSpawner.generated.h"

UCLASS()
class ZOMBIEAPOCALYPSE_API APopulationSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APopulationSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	FVector GetRandomSpawnPoint();
	TArray<ACustomPawnBase*> SpawnActors(int AmountToSpawn, TSubclassOf<ACustomPawnBase> SpawnClass);
	int AmountOfActorsInArray(TArray<ACustomPawnBase*> ActorArray);
	
	void AddBittenToArray(AZombie* BittenToAdd);
	void AddZombieToArray(AZombie* ZombieToAdd);


	
	UFUNCTION()
	void OnZombieSphereBeginOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);
	
	
	void TryConvertHuman(AZombie* OwnerZombie, AHuman* Human);
	void TryConvertBitten(ABitten* Bitten);
	
	
	UFUNCTION(BlueprintCallable)
	void OnZombieSpawn(ACustomPawnBase* ZombieSpawned);
	UFUNCTION(BlueprintCallable)
	void OnHumanSpawn(ACustomPawnBase* HumanSpawned);
	UFUNCTION(BlueprintCallable)
	void OnBittenSpawn(ACustomPawnBase* BittenSpawn);

	
	UFUNCTION(BlueprintCallable)
	void OnZombieDestroy(AActor* ActorDestroyed);
	UFUNCTION(BlueprintCallable)
	void OnHumanDestroy(AActor* ActorDestroyed);
	UFUNCTION(BlueprintCallable)
	void OnBittenDestroy(AActor* ActorDestroyed);

	void SetupHUD();
	void UpdateHUD();
	
	
	
	
	
	
	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TSubclassOf<UCounterHUD> CounterHUDClass;
	UPROPERTY()
	UCounterHUD* CounterHUD;

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	float BittenTurningTime;
	/** Cooldown between bites so a single overlap can't convert repeatedly */
	UPROPERTY(EditDefaultsOnly, Category = "Bite")
	float ZombieBiteCooldown;
	
	FVector MapLenght;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (MakeEditWidget = "true", AllowPrivateAccess = "true"))
	int AmountZombiesToSpawnAtStart;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (MakeEditWidget = "true", AllowPrivateAccess = "true"))
	int AmountHumansToSpawnAtStart;

	// populations as actual objects
	TArray<ACustomPawnBase*> ZombiePopulation;
	TArray<ACustomPawnBase*> BittenPopulation;
	TArray<ACustomPawnBase*> HumanPopulation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (MakeEditWidget = "true", AllowPrivateAccess = "true"))
	int ZombiePopulationCount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (MakeEditWidget = "true", AllowPrivateAccess = "true"))
	int BittenPopulationCount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (MakeEditWidget = "true", AllowPrivateAccess = "true"))
	int HumanPopulationCount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (MakeEditWidget = "true", AllowPrivateAccess = "true"))
	int32 Time;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (MakeEditWidget = "true", AllowPrivateAccess = "true"))
	TSubclassOf<AZombie> ZombieClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (MakeEditWidget = "true", AllowPrivateAccess = "true"))
	TSubclassOf<ABitten> BittenClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (MakeEditWidget = "true", AllowPrivateAccess = "true"))
	TSubclassOf<AHuman> HumanClass;
};