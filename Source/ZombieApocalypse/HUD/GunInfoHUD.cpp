// Copyright University of Inland Norway


#include "GunInfoHUD.h"

void UGunInfoHUD::NativeConstruct()
{
	Super::NativeConstruct();
	
	UpdateReloadProgressBar(0);
}

void UGunInfoHUD::UpdateAllText()
{
}

void UGunInfoHUD::UpdateBulletCount(int8 NewBulletCount, int8 MaxBulletCount)
{
	BulletTextCounter -> SetText(FText::FromString(""));
	FText BulletCountText = FText::FromString( FString::Printf(TEXT("%d / %d"), NewBulletCount, MaxBulletCount ));
	BulletTextCounter -> SetText(BulletCountText);
}

void UGunInfoHUD::UpdateReloadProgressBar(float ReloadProgressPercentile)
{
	UE_LOG(LogTemp, Warning, TEXT("Reloading %f"), ReloadProgressPercentile);
	ReloadProgressBar -> SetPercent(ReloadProgressPercentile);
}

