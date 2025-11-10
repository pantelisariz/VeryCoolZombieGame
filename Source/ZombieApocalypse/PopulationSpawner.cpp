// Copyright University of Inland Norway

#include "PopulationSpawner.h"

#include "NavigationSystem.h"
#include "NavMesh/RecastNavMesh.h"
#include "SimulationController.h"
#include "Field/FieldSystemNodes.h"

// Sets default values
APopulationSpawner::APopulationSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MapLenght = FVector(0,0,0);
	
	AmountZombiesToSpawnAtStart = 1;
	AmountHumansToSpawnAtStart = 100;

	ZombiePopulationCount = 0;
	BittenPopulationCount = 0;
	HumanPopulationCount = 0;

}

// Called when the game starts or when spawned
void APopulationSpawner::BeginPlay()
{
	Super::BeginPlay();
	
	HumanPopulation = SpawnActors(AmountHumansToSpawnAtStart, HumanClass);
	HumanPopulationCount = AmountOfActorsInArray(HumanPopulation);

	ZombiePopulation = SpawnActors(AmountZombiesToSpawnAtStart, ZombieClass);
	ZombiePopulationCount = AmountOfActorsInArray(ZombiePopulation);

}

// Called every frame
void APopulationSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
FVector APopulationSpawner::GetRandomSpawnPoint()
{
	// auto* const NavSys = UNavigationSystemV1::GetCurrent(GetWorld());
	UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>( GetWorld() );
	if (not NavSys)
	{
		return FVector(0,0,0);
	}
	ARecastNavMesh* NavMesh = Cast<ARecastNavMesh>( NavSys -> GetDefaultNavDataInstance() );
	
	if (not NavMesh)
	{
		return FVector(0,0,0);
	}
	FNavLocation Loc;
	if (not NavMesh -> GetRandomPointInNavigableRadius(GetActorLocation(), 10000.f, Loc))
	{
		return FVector(0,0,0);
	}
	
	return Loc.Location;
}

TArray<AActor*> APopulationSpawner::SpawnActors(int AmountToSpawn, TSubclassOf<ACustomPawnBase> SpawnClass)
{
	TArray<FVector> SpawnPoints;
	TArray<AActor*> SpawnedActors;
	
	for (int i = 0; i < AmountToSpawn; i++)
	{
		bool bCanSpawn = false;
		FVector RandomSpawnPoint;
		
		while (!bCanSpawn)
		{
			RandomSpawnPoint = GetRandomSpawnPoint();
			
			if (SpawnPoints.Contains(RandomSpawnPoint))
			{
				continue;
			}
			bCanSpawn = true;
		}

		
		SpawnPoints.Add(RandomSpawnPoint);

		ACustomPawnBase* SpawnedActor = GetWorld() -> SpawnActor<ACustomPawnBase>(SpawnClass, RandomSpawnPoint, FRotator(0,0,0));
		SpawnedActor -> SpawnDefaultController();
		SpawnedActors.Add(SpawnedActor);
		// GEngine -> AddOnScreenDebugMessage(-1, 10.0f, FColor::Purple, FString::Printf(TEXT("Spawned a Human")) );
	}
	
	return SpawnedActors;
}

int APopulationSpawner::AmountOfActorsInArray(TArray<AActor*> ActorArray)
{
	int AmountOfActors = ActorArray.Num();
	return AmountOfActors;
}

void APopulationSpawner::CullHumanActor(AHuman* TargetHuman)
{
	BittenPopulation.Add(
	GetWorld() -> SpawnActor<ABitten>(BittenClass, TargetHuman->GetActorLocation(), FRotator(0,0,0))
	);
	HumanPopulation.Remove(TargetHuman);
}

void APopulationSpawner::UpdatePopulationCount(AHuman* TargetHuman)
{
	CullHumanActor(TargetHuman);
}

