// Copyright University of Inland Norway

#pragma once

#include "CoreMinimal.h"
#include "GunAttachment.h"
#include "Components/ActorComponent.h"
#include "GunAttachmentSlotComponent.generated.h"

	
UCLASS(Blueprintable, BlueprintType, EditInlineNew, ClassGroup = (Gun), meta = (BlueprintSpawnableComponent))

class ZOMBIEAPOCALYPSE_API UGunAttachmentSlotComponent : public UStaticMeshComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGunAttachmentSlotComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
    virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
	void SetUpAttachmentOnClassChange(FPropertyChangedEvent& PropertyChangedEvent);
	void CreateAttachment();
	void SpawnAttachment();

	

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attachment", meta = ( AllowPrivateAccess="true"))
	bool bIsSlotEnabled;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attachment", meta = ( AllowPrivateAccess="true"))
	TArray<TSubclassOf<AGunAttachment>> AttachmentClasses;
	TArray<AGunAttachment*> Attachments;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attachment", meta = ( AllowPrivateAccess="true"))
	TSubclassOf<AGunAttachment> CurrentAttachmentClass;
	AGunAttachment* CurrentAttachment;
	
};
