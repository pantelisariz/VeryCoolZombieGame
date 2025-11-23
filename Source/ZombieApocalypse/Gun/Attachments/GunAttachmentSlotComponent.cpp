// Copyright University of Inland Norway


#include "GunAttachmentSlotComponent.h"

// Sets default values for this component's properties
UGunAttachmentSlotComponent::UGunAttachmentSlotComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
	
	bIsSlotEnabled = false;
	
	CurrentAttachmentClass = nullptr;
	CurrentAttachment = nullptr;

	// ...
}


// Called when the game starts
void UGunAttachmentSlotComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	if (CurrentAttachmentClass and not CurrentAttachment and bIsSlotEnabled)
	{
		SpawnAttachment();
	}
}



void UGunAttachmentSlotComponent::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	
	Modify();
	
	SetUpAttachmentOnClassChange(PropertyChangedEvent);
}



void UGunAttachmentSlotComponent::SetUpAttachmentOnClassChange(FPropertyChangedEvent& PropertyChangedEvent)
{
	
	if (PropertyChangedEvent.Property and 
	PropertyChangedEvent.Property->GetFName() == GET_MEMBER_NAME_CHECKED(UGunAttachmentSlotComponent, CurrentAttachmentClass))
	{
		if (not bIsSlotEnabled)
		{
			return;
		}
		CreateAttachment();
        
		// Mark package as dirty to save changes
		if (GetOuter())
		{
			GetOuter() -> MarkPackageDirty();
		}
	}
}



void UGunAttachmentSlotComponent::CreateAttachment()
{
	
	if (CurrentAttachment and CurrentAttachment -> IsValidLowLevel())
	{
		UE_LOG(LogTemp, Warning, TEXT("%s Attachment is valid"), *CurrentAttachment -> GetClass() -> GetDisplayNameText().ToString() );
		UE_LOG(LogTemp, Warning, TEXT("Attempt to destroy"));
		DestroyAttachment();
		CurrentAttachment = nullptr;
	}
	
	
	if (not CurrentAttachment)
	{
		UE_LOG(LogTemp, Warning, TEXT("Current Attachment is a nullptr, before checking class"));
		CurrentAttachment = nullptr;
	}
	
	
	if (not CurrentAttachmentClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("Current Attachment Class is a nullptr"));
		CurrentAttachment = nullptr;
		return;
	}
	
	
	if (not AttachmentClasses.Contains(CurrentAttachmentClass))
	{
		UE_LOG(LogTemp, Warning, TEXT("Class is not a viable attachment"));
		CurrentAttachment = nullptr;
		return;
	}
	
	
	SpawnAttachment();
	UE_LOG(LogTemp, Warning, TEXT("%s Attachment is spawned"), *CurrentAttachment -> GetClass() -> GetDisplayNameText().ToString() );
}



void UGunAttachmentSlotComponent::SpawnAttachment()
{
	UE_LOG(LogTemp, Warning, TEXT("Spawns Actor"));
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParams.Owner = GetOwner();
	
	AGunAttachment* SpawnedAttachment = GetWorld() -> SpawnActor<AGunAttachment>(CurrentAttachmentClass,  FVector(0, 0, 0), FRotator(0,0,0), SpawnParams);
	CurrentAttachment = SpawnedAttachment;
	
	FAttachmentTransformRules AttachmentRules(EAttachmentRule::KeepRelative, true);
	CurrentAttachment -> AttachToComponent(this, AttachmentRules);
	
	CurrentAttachment -> SetFlags(RF_Transactional);
	UE_LOG(LogTemp, Warning, TEXT("%s Attachment is spawned"), *CurrentAttachment -> GetClass() -> GetDisplayNameText().ToString() );
}



void UGunAttachmentSlotComponent::DestroyAttachment()
{
	CurrentAttachment -> DestroyAttachment();
	CurrentAttachment = nullptr;
}







// Called every frame
void UGunAttachmentSlotComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

