// Copyright University of Inland Norway


#include "Bitten.h"

// Sets default values
ABitten::ABitten()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABitten::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABitten::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABitten::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

