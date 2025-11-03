// Copyright University of Inland Norway

#include "SimulationController.h"
#include "PopulationSpawner.h"

#include "Field/FieldSystemNodes.h"

// Sets default values
APopulationSpawner::APopulationSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MapLenght = FVector(0,0,0);
	AmountZombiesToSpawnAtStart = 1;
	AmountHumansToSpawnAtStart = 100;

}

// Called when the game starts or when spawned
void APopulationSpawner::BeginPlay()
{
	Super::BeginPlay();

	MapLenght.X = (Corners[0].GetAbs().X) + (Corners[3].GetAbs().X);
	MapLenght.Y = (Corners[0].GetAbs().Y) + (Corners[1].GetAbs().Y);
	GEngine -> AddOnScreenDebugMessage(-1, 10.0f, FColor::Purple, FString::Printf(TEXT("Map Lenght X: %f"), MapLenght.X) );
	GEngine -> AddOnScreenDebugMessage(-1, 10.0f, FColor::Purple, FString::Printf(TEXT("Map Lenght Y: %f"), MapLenght.Y) );

	/*
	float TotalPoints = MapLenght.X * MapLenght.Y;
	float TotalSpawnablePoints = TotalPoints / AmountHumansToSpawnAtStart;

	GEngine -> AddOnScreenDebugMessage(-1, 10.0f, FColor::Purple, FString::Printf(TEXT("Total Points: %f"), TotalPoints) );
	GEngine -> AddOnScreenDebugMessage(-1, 10.0f, FColor::Purple, FString::Printf(TEXT("Total Spawnable Points: %f"), TotalSpawnablePoints) );
	*/
	
	HumanPopulation = SpawnActors(AmountHumansToSpawnAtStart, HumanClass);
}

// Called every frame
void APopulationSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
FVector APopulationSpawner::GetRandomSpawnPoint()
{
	FVector RandomSpawnPoint = FVector( FMath::FRandRange(Corners[0].X, Corners[3].X ), FMath::FRandRange(Corners[0].Y, Corners[1].Y ), 0 );

	return RandomSpawnPoint;
}

TArray<AActor*> APopulationSpawner::SpawnActors(int AmountToSpawn, TSubclassOf<AActor> SpawnClass)
{
	TArray<FVector> SpawnPoints;
	TArray<AActor*> SpawnActors;
	
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
		SpawnActors.Add(
			GetWorld() -> SpawnActor<AActor>(SpawnClass, RandomSpawnPoint, FRotator(0,0,0))
			);
		GEngine -> AddOnScreenDebugMessage(-1, 10.0f, FColor::Purple, FString::Printf(TEXT("Spawned a Human")) );
	}
	return SpawnActors;
}
