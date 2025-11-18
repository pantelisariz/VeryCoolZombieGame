// Copyright University of Inland Norway


#include "Gun.h"

// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	/*
	 * Here you can set the default stats of the gun
	 */
	Damage = 10;
	FireRate = 3;
	Range = 1000;
	ReloadTime = 3;
	MaxAmmoCount = 6;
	CurrentAmmoCount = MaxAmmoCount;

}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

