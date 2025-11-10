// Copyright University of Inland Norway

#pragma once

#include "CoreMinimal.h"
#include "Engine/TargetPoint.h"
#include "GameFramework/Actor.h"
#include "AI/Zombie.h"
#include "AI/Human.h"
#include "AI/Bitten.h"
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
	TArray<AActor*> SpawnActors(int AmountToSpawn, TSubclassOf<AActor> SpawnClass);
	int AmountOfActorsInArray(TArray<AActor*> ActorArray);

	void CullHumanActor(AHuman* TargetHuman);
	void UpdatePopulationCount(AHuman* TargetHuman);

	FVector MapLenght;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (MakeEditWidget = "true", AllowPrivateAccess = "true"))
	int AmountZombiesToSpawnAtStart;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (MakeEditWidget = "true", AllowPrivateAccess = "true"))
	int AmountHumansToSpawnAtStart;

	// populations as actual objects
	TArray<AActor*> ZombiePopulation;
	TArray<AActor*> BittenPopulation;
	TArray<AActor*> HumanPopulation;

	
	int ZombiePopulationCount;
	int BittenPopulationCount;
	int HumanPopulationCount;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (MakeEditWidget = "true", AllowPrivateAccess = "true"))
	TSubclassOf<AZombie> ZombieClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (MakeEditWidget = "true", AllowPrivateAccess = "true"))
	TSubclassOf<ABitten> BittenClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (MakeEditWidget = "true", AllowPrivateAccess = "true"))
	TSubclassOf<AHuman> HumanClass;
};

