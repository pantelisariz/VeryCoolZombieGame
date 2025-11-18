// Copyright University of Inland Norway


#include "GunInfoHUD.h"

void UGunInfoHUD::NativeConstruct()
{
	Super::NativeConstruct();
	
	BulletCount = 0;
}

void UGunInfoHUD::UpdateAllText()
{
}

void UGunInfoHUD::UpdateBulletCount(int32 NewBulletCount)
{
	FText BulletCountText = FText::FromString( FString::Printf(TEXT("%d / %d MaxBulletCount"), (int)NewBulletCount, (int)MaxBulletCount ));
	BulletTextCounter -> SetText(BulletCountText);
}
