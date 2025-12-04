// Copyright University of Inland Norway

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GunAttachment.generated.h"


UENUM(BlueprintType)
enum class EGunStatType : uint8
{
	Damage,
	FireRate,
	Range,
	ReloadTime,
	MagazineCapacity,
	CurrentCarryAmmo,
	MaxCarryAmmo,
	BulletPerAmmo,
	AmmoUsedPerShot
};



UCLASS()
class ZOMBIEAPOCALYPSE_API AGunAttachment : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGunAttachment();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	void DestroyAttachment();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attachment", meta = (AllowPrivateAccess = "true"))
	TMap<EGunStatType, float> AttachmentStatChange;

};
