// Copyright University of Inland Norway


#include "GunAttachmentSlotComponent.h"

#include "ZombieApocalypse/AllDelegates.h"

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

#if WITH_EDITOR
void UGunAttachmentSlotComponent::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	SetUpAttachmentOnClassChange(PropertyChangedEvent);
}
#endif


void UGunAttachmentSlotComponent::PostLoad()
{
	Super::PostLoad();
	if (not IsRunningGame() and CurrentAttachmentClass and not CurrentAttachment)
	{
		CreateAttachment();
	}
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
	}
}



void UGunAttachmentSlotComponent::CreateAttachment()
{
	UE_LOG(LogTemp, Warning, TEXT("Spawns Attachment"));
	
	if (CurrentAttachment and CurrentAttachment -> IsValidLowLevel())
	{
		UE_LOG(LogTemp, Warning, TEXT("Destroys Attachment"));
		CurrentAttachment->Destroy();
		CurrentAttachment = nullptr;
	}
    
	if (not CurrentAttachmentClass or not AttachmentClasses.Contains(CurrentAttachmentClass))
	{
		UE_LOG(LogTemp, Warning, TEXT("Attachment is not in list"));
		CurrentAttachment = nullptr;
		return;
	}
    
	// Only spawn if we're in the game world
	if (GetWorld() and GetWorld() -> WorldType == EWorldType::Game)
	{
		SpawnAttachment();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Spawns Gun-Attachment in editor"));
		
		SpawnAttachment();
		
	}
}



void UGunAttachmentSlotComponent::SpawnAttachment()
{
	UE_LOG(LogTemp, Warning, TEXT("Spawns Gun-Attachment"));
	
	CurrentAttachment = GetWorld() -> SpawnActor<AGunAttachment>(CurrentAttachmentClass, FVector(0,0,0), FRotator(0,0,0));
	
	if (not CurrentAttachment)
	{
		return;
	}
	
	CurrentAttachment -> AttachToComponent(this, FAttachmentTransformRules::KeepRelativeTransform);
	
	// UE_LOG(LogTemp, Warning, TEXT("%s Attachment is spawned"), *CurrentAttachment -> GetClass() -> GetDisplayNameText().ToString() );
	if (not CurrentAttachment)
	{
		return;
	}
	
	UE_LOG(LogTemp, Warning, TEXT("Amount of stat changes: %d"), CurrentAttachment -> AttachmentStatChange.Num());
	
	
	AttachmentStatChange = CurrentAttachment -> AttachmentStatChange;
	AttachmentCreated.Broadcast(CurrentAttachment -> AttachmentStatChange);
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

