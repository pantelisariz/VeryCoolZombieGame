// Copyright University of Inland Norway


#include "GunAttachmentSlotComponent.h"

// Sets default values for this component's properties
UGunAttachmentSlotComponent::UGunAttachmentSlotComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
	
	bIsSlotEnabled = false;
	

	// ...
}


// Called when the game starts
void UGunAttachmentSlotComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}



void UGunAttachmentSlotComponent::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	SetUpAttachmentOnClassChange(PropertyChangedEvent);
}



void UGunAttachmentSlotComponent::SetUpAttachmentOnClassChange(FPropertyChangedEvent& PropertyChangedEvent)
{
	if (PropertyChangedEvent.Property and 
	PropertyChangedEvent.Property->GetFName() == GET_MEMBER_NAME_CHECKED(UGunAttachmentSlotComponent, CurrentAttachmentClass))
	{
		if (not CurrentAttachmentClass)
		{
			if (CurrentAttachment)
			{
				CurrentAttachment -> ConditionalBeginDestroy();
				CurrentAttachment -> Destroy();
				CurrentAttachment = nullptr;
			}
			return;
		}
		
		if (not bIsSlotEnabled)
		{
			return;
		}
		
		CreateAttachment();
	}
}



void UGunAttachmentSlotComponent::CreateAttachment()
{
	if (CurrentAttachment and CurrentAttachment -> IsValidLowLevel())
	{
		CurrentAttachment -> ConditionalBeginDestroy();
		CurrentAttachment -> Destroy();
		CurrentAttachment = nullptr;
	}
	
	if (not CurrentAttachmentClass)
	{
		return;
	}
	CurrentAttachment = NewObject<AGunAttachment>(this, CurrentAttachmentClass);
	if (not CurrentAttachment)
	{
		return;
	}
	CurrentAttachment -> SetFlags(RF_Transactional);
	SpawnAttachment();
}

void UGunAttachmentSlotComponent::SpawnAttachment()
{
	CurrentAttachment = GetWorld() -> SpawnActor<AGunAttachment>(CurrentAttachmentClass,  FVector(0, 0, 0), FRotator(0,0,0));
	FAttachmentTransformRules AttachmentRules(EAttachmentRule::KeepRelative, true);
	CurrentAttachment -> AttachToComponent(this, AttachmentRules);
}


// Called every frame
void UGunAttachmentSlotComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

