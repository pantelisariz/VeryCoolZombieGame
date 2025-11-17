// Copyright University of Inland Norway


#include "CounterHUD.h"

void UCounterHUD::NativeConstruct()
{
	Super::NativeConstruct();
	ZombiePopulation = 0;
	BittenPopulation = 0;
	HumanPopulation = 0;

	UpdateAllText();
}

void UCounterHUD::UpdateAllText()
{
	SetZombieTextCounter();
	SetBittenTextCounter();
	SetHumanTextCounter();
}


void UCounterHUD::SetZombieTextCounter()
{
	FText ZombieText = FText::FromString( FString::Printf(TEXT("Amount of Zombies: %d"), (int)ZombiePopulation) );
	ZombieTextCounter -> SetText(ZombieText);
}



void UCounterHUD::SetBittenTextCounter()
{
	FText BittenText = FText::FromString( FString::Printf(TEXT("Amount of Bitten: %d"), (int)BittenPopulation) );
	BittenTextCounter -> SetText(BittenText);
}



void UCounterHUD::SetHumanTextCounter()
{
	FText HumanText = FText::FromString( FString::Printf(TEXT("Amount of Humans: %d"), (int)HumanPopulation) );
	HumanTextCounter -> SetText(HumanText);
}
