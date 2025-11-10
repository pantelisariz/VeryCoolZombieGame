// Copyright University of Inland Norway


#include "../PlayerCharacter\Overlord.h"

// Sets default values
AOverlord::AOverlord()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AOverlord::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AOverlord::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AOverlord::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

