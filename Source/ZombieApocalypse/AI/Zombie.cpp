// Copyright University of Inland Norway


#include "Zombie.h"

#include "Human.h"
#include "Kismet/GameplayStatics.h"
#include "ZombieApocalypse/PopulationSpawner.h"

// Sets default values
AZombie::AZombie()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereCollider = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Collider"));
	SphereCollider -> OnComponentBeginOverlap.AddDynamic( this, &AZombie::Interact );

}

// Called when the game starts or when spawned
void AZombie::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AZombie::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AZombie::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

// Inherited function

void AZombie::Interact(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit)
{
	if ( OtherActor -> GetClass() -> IsChildOf(AHuman::StaticClass()) )
	{
		return;
	}

	TArray<AActor*> FoundPopSpawners;
	// Atheist91. (2015, August). “Get All Actors Of Class” in C++. Retrieved from Unreal Engine: https://forums.unrealengine.com/t/get-all-actors-of-class-in-c/329740/4
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APopulationSpawner::StaticClass(), FoundPopSpawners);
	
	auto* const CastPopulationSpawner = Cast<APopulationSpawner>(FoundPopSpawners[0]);
	if (not CastPopulationSpawner)
	{
		return;
	}
	
	APlayerController* PlayerCharacterController = Cast<APlayerController>(GetWorld()->GetFirstPlayerController());
	if (not PlayerCharacterController)
	{
		return;
	}
	PopulationSpawner = CastPopulationSpawner;
		
}
