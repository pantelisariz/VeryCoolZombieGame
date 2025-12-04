// Copyright University of Inland Norway


#include "GunCombatHUD.h"

void UGunCombatHUD::NativeConstruct()
{
	Super::NativeConstruct();
	
	UpdateReloadProgressBar(0);
}

void UGunCombatHUD::UpdateAllText()
{
}

void UGunCombatHUD::UpdateBulletCount(int32 NewBulletCount, int32 TotalAmmo)
{
	BulletTextCounter -> SetText(FText::FromString(""));
	FText BulletCountText = FText::FromString( FString::Printf(TEXT("%d / %d"), NewBulletCount, TotalAmmo ));
	BulletTextCounter -> SetText(BulletCountText);
}

void UGunCombatHUD::UpdateReloadProgressBar(float ReloadProgressPercentile)
{
	// UE_LOG(LogTemp, Warning, TEXT("Reloading %f"), ReloadProgressPercentile);
	ReloadProgressBar -> SetPercent(ReloadProgressPercentile);
}

