// Copyright University of Inland Norway


#include "GunAttachment.h"

// Sets default values
AGunAttachment::AGunAttachment()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SetActorEnableCollision(false);
}

// Called when the game starts or when spawned
void AGunAttachment::BeginPlay()
{
	Super::BeginPlay();
	
	SetActorEnableCollision(false);
	
}

// Called every frame
void AGunAttachment::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGunAttachment::DestroyAttachment()
{
	DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
    
	Destroy();
}

