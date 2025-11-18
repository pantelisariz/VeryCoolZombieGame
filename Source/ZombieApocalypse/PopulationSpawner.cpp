// Copyright University of Inland Norway

#include "PopulationSpawner.h"

#include "NavigationSystem.h"
#include "NavMesh/RecastNavMesh.h"
#include "Field/FieldSystemNodes.h"
#include "Kismet/GameplayStatics.h"

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
	Time = 0;
	
	ZombieBiteCooldown = 15.0f;
	
}

// Called when the game starts or when spawned
void APopulationSpawner::BeginPlay()
{
	Super::BeginPlay();
	
	SetupHUD();
	
	HumanPopulation = SpawnActors(AmountHumansToSpawnAtStart, HumanClass);
	HumanPopulationCount = AmountOfActorsInArray(HumanPopulation);

	ZombiePopulation = SpawnActors(AmountZombiesToSpawnAtStart, ZombieClass);
	ZombiePopulationCount = AmountOfActorsInArray(ZombiePopulation);

	UpdateHUD();
}



// Called every frame
void APopulationSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Time = GetWorld() -> GetTimeSeconds();
	CounterHUD -> Time = Time;
	CounterHUD -> SetTimeTextCounter();
	// UE_LOG(LogTemp, Warning, TEXT("Time: %d"), Time);
	

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



TArray<ACustomPawnBase*> APopulationSpawner::SpawnActors(int AmountToSpawn, TSubclassOf<ACustomPawnBase> SpawnClass)
{
	TArray<FVector> SpawnPoints;
	TArray<ACustomPawnBase*> SpawnedActors;
	
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
		if (not SpawnedActor)
		{
			continue;
		}
		
		SpawnedActors.Add(SpawnedActor);

		if (SpawnedActor -> GetClass() == ZombieClass)
		{
			OnZombieSpawn(SpawnedActor);
		}
		else if (SpawnedActor -> GetClass() == HumanClass)
		{
			OnHumanSpawn(SpawnedActor);
		}
		else if (SpawnedActor -> GetClass() == BittenClass)
		{
			OnBittenSpawn(SpawnedActor);
		}
		
		// GEngine -> AddOnScreenDebugMessage(-1, 10.0f, FColor::Purple, FString::Printf(TEXT("Spawned a Human")) );
	}
	
	return SpawnedActors;
}



int APopulationSpawner::AmountOfActorsInArray(TArray<ACustomPawnBase*> ActorArray)
{
	int AmountOfActors = ActorArray.Num();
	return AmountOfActors;
}



void APopulationSpawner::AddBittenToArray(AZombie* BittenToAdd)
{
	BittenPopulation.Add(BittenToAdd);
}



void APopulationSpawner::AddZombieToArray(AZombie* ZombieToAdd)
{
	ZombiePopulation.Add(ZombieToAdd);
}



void APopulationSpawner::OnZombieDestroy(AActor* ActorDestroyed)
{
	AZombie* ZombieCast = Cast<AZombie>(ActorDestroyed);
	if (not ZombieCast)
	{
		return;
	}
	
	ZombiePopulationCount = ZombiePopulation.Num();
	
	CounterHUD -> ZombiePopulationCount = ZombiePopulationCount;
	CounterHUD -> SetZombieTextCounter();

	ZombiePopulation.Remove(ZombieCast);
}



void APopulationSpawner::OnHumanDestroy(AActor* ActorDestroyed)
{
	AHuman* HumanCast = Cast<AHuman>(ActorDestroyed);
	if (not HumanCast)
	{
		return;
	}
	HumanPopulation.Remove(HumanCast);

	HumanPopulationCount = HumanPopulation.Num();
	CounterHUD -> HumanPopulationCount = HumanPopulationCount;
	CounterHUD -> SetHumanTextCounter();
	
}



void APopulationSpawner::OnBittenDestroy(AActor* ActorDestroyed)
{
	ABitten* BittenCast = Cast<ABitten>(ActorDestroyed);
	if (not BittenCast)
	{
		return;
	}
	BittenPopulation.Remove(BittenCast);
	
	TryConvertBitten(BittenCast);
	
	BittenPopulationCount = BittenPopulation.Num();
	CounterHUD -> BittenPopulationCount = BittenPopulationCount;
	CounterHUD -> SetBittenTextCounter();
}



void APopulationSpawner::SetupHUD()
{
	auto PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	APlayerController* CastPlayerController = Cast<APlayerController>(PlayerController);
	if (not CastPlayerController)
	{
		return;
	}
	CounterHUD = CreateWidget<UCounterHUD>(CastPlayerController, *(CounterHUDClass));
	
	check(CounterHUD);

	CounterHUD -> ZombiePopulationCount = ZombiePopulationCount;
	CounterHUD -> BittenPopulationCount = BittenPopulationCount;
	CounterHUD -> HumanPopulationCount = HumanPopulationCount;
	
	CounterHUD -> AddToViewport();
}



void APopulationSpawner::UpdateHUD()
{
	ZombiePopulationCount = AmountOfActorsInArray(ZombiePopulation);
	BittenPopulationCount = AmountOfActorsInArray(BittenPopulation);
	HumanPopulationCount = AmountOfActorsInArray(HumanPopulation);
	Time = GetWorld() -> GetTimeSeconds();
	
	CounterHUD -> ZombiePopulationCount = ZombiePopulationCount;
	CounterHUD -> BittenPopulationCount = BittenPopulationCount;
	CounterHUD -> HumanPopulationCount = HumanPopulationCount;
	CounterHUD -> Time = Time;

	CounterHUD -> UpdateAllText();
}





//here will do the overlap
void APopulationSpawner::OnZombieSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (not OtherActor or OtherActor == this) 
	{
		return;
	}

	AHuman* HumanCast = Cast<AHuman>(OtherActor);
	if (not HumanCast)
	{
		return;
	}
	AActor* OwnerActor = OverlappedComponent -> GetAttachParentActor();
	AZombie* ZombieCast = Cast<AZombie>(OwnerActor);
	if (not ZombieCast)
	{
		return;
	}
	
	TryConvertHuman(ZombieCast, HumanCast);
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Overlapped"));
	
}




//The function making him into bitten guy or gal
void APopulationSpawner::TryConvertHuman(AZombie* OwnerZombie, AHuman* Human)
{
	if (not Human)
	{
		return;
	}

	const float Now = GetWorld()->GetTimeSeconds();
	if (Now - OwnerZombie ->  LastBiteTime < ZombieBiteCooldown)
	{
		return;
	}
	OwnerZombie -> LastBiteTime = Now;

	const FTransform SpawnTransform = Human->GetActorTransform();
	//Unsure if there is a controller in this bad boy still doing this shit to save it.
	AController* OldController = Human->GetController();
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	
	//You have to set the bittenclass on the zombie bp!
	if (!BittenClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("AZombie::TryConvertHuman - BittenClass not set"));
		
		return;
	}
	
	
	// Spawn the bitten actor
	ABitten* NewBitten = GetWorld()->SpawnActor<ABitten>(BittenClass, SpawnTransform, SpawnParams);
	if (!NewBitten)
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to spawn the guy that got chomped"));
		
		return;
	}
	
	
	// Transfer controller (works for PlayerController or AIController that was possessing the human)
	if (OldController)
	{
		OldController->UnPossess();
		OldController->Possess(NewBitten);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("here was no controller in the human bitch"));
		
	}
	
	//my favorite part
	GetWorldTimerManager().SetTimer(NewBitten -> BittenTurningTimerHandle, NewBitten, &ABitten::ComposeAfterTime, BittenTurningTime, false);
	Human -> Destroy();
	
	OnBittenSpawn(NewBitten);
}



void APopulationSpawner::TryConvertBitten(ABitten* Bitten)
{
	if ( not Bitten)
	{
		UE_LOG(LogTemp, Warning, TEXT("Bitten is nullptr"));
		return;
	}
	
	
	const FTransform SpawnTransform = Bitten->GetActorTransform();
	//Unsure if there is a controller in this bad boy still doing this shit to save it.
	AController* OldController = Bitten -> GetController();
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	
	if (not ZombieClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("ZombieClass is nullptr"));
		return;
	}
	
	AZombie* NewZombie = GetWorld( )-> SpawnActor<AZombie>(ZombieClass, SpawnTransform, SpawnParams);
	
	
	if (OldController)
	{
		// UE_LOG(LogTemp, Warning, TEXT("Bitten has controller"));
		OldController -> UnPossess();
		OldController -> Possess(NewZombie);
	}
	
	CounterHUD -> SetZombieTextCounter();
	Bitten -> Destroy();
	
	OnZombieSpawn(NewZombie);
}



void APopulationSpawner::OnZombieSpawn(ACustomPawnBase* ZombieSpawned)
{
	AZombie* ZombieCast = Cast<AZombie>(ZombieSpawned);
	if (not ZombieCast)
	{
		return;
	}
	
	
	
	if (not ZombiePopulation.Contains(ZombieCast))
	{
		ZombiePopulation.Add(ZombieCast);
	}
	
	
	ZombieCast -> OnDestroyed.AddDynamic(this, &APopulationSpawner::OnZombieDestroy);
	if (ZombieCast -> SphereCollider)
	{
		ZombieCast -> SphereCollider->OnComponentBeginOverlap.AddDynamic(this, &APopulationSpawner::OnZombieSphereBeginOverlap);
	}
	
	ZombiePopulationCount = AmountOfActorsInArray(ZombiePopulation);
	CounterHUD -> ZombiePopulationCount = ZombiePopulationCount;
	CounterHUD -> SetZombieTextCounter();
}



void APopulationSpawner::OnHumanSpawn(ACustomPawnBase* HumanSpawned)
{
	AHuman* HumanCast = Cast<AHuman>(HumanSpawned);
	if (not HumanCast)
	{
		return;
	}
	
	
	if (not HumanPopulation.Contains(HumanCast))
	{
		HumanPopulation.Add(HumanCast);
	}
	
	HumanCast -> OnDestroyed.AddDynamic(this, &APopulationSpawner::OnHumanDestroy);
	
	HumanPopulationCount = AmountOfActorsInArray(HumanPopulation);
	
	// UE_LOG(LogTemp, Warning, TEXT("Human pop: %d"), HumanPopulationCount);
	// UE_LOG(LogTemp, Warning, TEXT("Human pop in HUD: %d"), CounterHUD -> HumanPopulationCount);
	
	CounterHUD -> HumanPopulationCount = HumanPopulationCount;
	CounterHUD -> SetHumanTextCounter();
}



void APopulationSpawner::OnBittenSpawn(ACustomPawnBase* BittenSpawn)
{
	ABitten* BittenCast = Cast<ABitten>(BittenSpawn);
	if (not BittenCast)
	{
		return;
	}
	
	
	if (not BittenPopulation.Contains(BittenCast))
	{
		BittenPopulation.Add(BittenCast);
	}
	
	BittenCast -> OnDestroyed.AddDynamic(this, &APopulationSpawner::OnBittenDestroy);
	BittenPopulationCount = AmountOfActorsInArray(BittenPopulation);
	CounterHUD -> BittenPopulationCount = BittenPopulationCount;
	CounterHUD -> SetBittenTextCounter();
}
