// Copyright University of Inland Norway

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ZombieApocalypse/Gun/Gun.h"
#include "PurchasableGunInfoHUD.generated.h"

/**
 * 
 */
UCLASS()
class ZOMBIEAPOCALYPSE_API UPurchasableGunInfoHUD : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void NativeConstruct() override;
	
	void SetGun(AGun* GunToSet);
	AGun* GetGun();
	void SetGunInfo();

	
protected:
	UPROPERTY()
	AGun* CurrentGun;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	UTextBlock* GunInfoText;
};
