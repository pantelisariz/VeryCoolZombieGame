// Copyright University of Inland Norway


#include "GunAttachment.h"

// Sets default values
AGunAttachment::AGunAttachment()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGunAttachment::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGunAttachment::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

