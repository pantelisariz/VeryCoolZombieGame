// Copyright University of Inland Norway


#include "CombatHUD.h"

void UCombatHUD::NativeConstruct()
{
	Super::NativeConstruct();
	
	UpdateReloadProgressBar(0);
}

void UCombatHUD::UpdateAllText()
{
}

void UCombatHUD::UpdateBulletCount(int32 NewBulletCount, int32 TotalAmmo)
{
	BulletTextCounter -> SetText(FText::FromString(""));
	FText BulletCountText = FText::FromString( FString::Printf(TEXT("%d / %d"), NewBulletCount, TotalAmmo ));
	BulletTextCounter -> SetText(BulletCountText);
}

void UCombatHUD::UpdateReloadProgressBar(float ReloadProgressPercentile)
{
	// UE_LOG(LogTemp, Warning, TEXT("Reloading %f"), ReloadProgressPercentile);
	ReloadProgressBar -> SetPercent(ReloadProgressPercentile);
}

