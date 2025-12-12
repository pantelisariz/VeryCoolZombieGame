// Copyright University of Inland Norway

#pragma once

#include "CoreMinimal.h"
#include "GunAttachment.h"
#include "Components/ActorComponent.h"
#include "GunAttachmentSlotComponent.generated.h"



DECLARE_MULTICAST_DELEGATE_TwoParams(FAttachmentCreatedDelegate, TMap<EGunStatType, FGunStatChange> /*AttachmentStatChanges*/);

	
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
#if WITH_EDITOR
    virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif
	virtual void PostLoad() override;

	
	void SetUpAttachmentOnClassChange(FPropertyChangedEvent& PropertyChangedEvent);
	
public:	
	void CreateAttachment();
	void SpawnAttachment();
	void DestroyAttachment();
	
	

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attachment", meta = ( AllowPrivateAccess="true"))
	bool bIsSlotEnabled;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attachment", meta = ( AllowPrivateAccess="true"))
	TArray<TSubclassOf<AGunAttachment>> AttachmentClasses;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attachment", meta = ( AllowPrivateAccess="true"))
	TSubclassOf<AGunAttachment> CurrentAttachmentClass;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attachment", meta = ( AllowPrivateAccess="true"))
	AGunAttachment* CurrentAttachment;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Attachment", meta = (AllowPrivateAccess = "true"))
	TMap<EGunStatType, FGunStatChange> AttachmentStatChange;
	
	
	FAttachmentCreatedDelegate AttachmentCreated;
	
	
private:
	TArray<AGunAttachment*> Attachments;
	
};
