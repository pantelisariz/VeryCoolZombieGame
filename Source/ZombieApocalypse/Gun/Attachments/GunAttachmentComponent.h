// Copyright University of Inland Norway

#pragma once

#include "CoreMinimal.h"
#include "GunAttachment.h"
#include "Components/ActorComponent.h"
#include "GunAttachmentComponent.generated.h"

	
UCLASS(Blueprintable, BlueprintType, EditInlineNew, ClassGroup = (Gun), meta = (BlueprintSpawnableComponent))

class ZOMBIEAPOCALYPSE_API UGunAttachmentComponent : public UStaticMeshComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGunAttachmentComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attachment", meta = ( AllowPrivateAccess="true"))
	TArray<TSubclassOf<AGunAttachment>> Attachment;
	
	
	/*
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Transform", meta=(AllowPrivateAccess="true", LinearDeltaSensitivity = "1", Delta = "1.0"))
	FVector RelativeLocation;
	*/
		
};
