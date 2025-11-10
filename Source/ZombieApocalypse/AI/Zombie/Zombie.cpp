// Copyright University of Inland Norway


#include "Zombie.h"

#include "../Human//Human.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AZombie::AZombie()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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
	
	
	APlayerController* PlayerCharacterController = Cast<APlayerController>(GetWorld()->GetFirstPlayerController());
	if (not PlayerCharacterController)
	{
		return;
	}
}
