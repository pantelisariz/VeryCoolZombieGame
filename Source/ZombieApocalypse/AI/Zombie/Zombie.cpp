// Copyright University of Inland Norway


#include "Zombie.h"
#include "../Bitten/Bitten.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Controller.h"

#include "../Human//Human.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AZombie::AZombie()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BiteCooldown = 1.0f;
	LastBiteTime = -BiteCooldown;

}

// Called when the game starts or when spawned
void AZombie::BeginPlay()
{
	Super::BeginPlay();
	if (SphereCollider)
	{
		SphereCollider->OnComponentBeginOverlap.AddDynamic(this, &AZombie::OnSphereBeginOverlap);
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString("Zombie has no SphereCollider"));
	}
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
//Pantelis No idea what the fuck is this so gonna write it my way
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



//here will do the overlap
void AZombie::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor || OtherActor == this) return;

	AHuman* Human = Cast<AHuman>(OtherActor);
	if (Human)
	{
		TryConvertHuman(Human);
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Overlapped"));
	}
}



//The function making him into bitten guy or gal
void AZombie::TryConvertHuman(AHuman* Human)
{
	if (!Human) return;

	const float Now = GetWorld()->GetTimeSeconds();
	if (Now - LastBiteTime < BiteCooldown) return;
	LastBiteTime = Now;

	const FTransform SpawnTransform = Human->GetActorTransform();
	//Unsure if there is a controller in this bad boy still doing this shit to save it.
	AController* OldController = Human->GetController();
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	//You have to set the bittenclass on the zombie bp!
	if (!BittenClass)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("AZombie::TryConvertHuman - BittenClass not set"));
		return;
	}
	// Spawn the bitten actor
	ABitten* NewBitten = GetWorld()->SpawnActor<ABitten>(BittenClass, SpawnTransform, SpawnParams);
	if (!NewBitten)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString("Failed to spawn the guy that got chomped"));
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
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString("There was no controller in the human bitch"));
	}
	//my favorite part
	
	Human->Destroy();
}