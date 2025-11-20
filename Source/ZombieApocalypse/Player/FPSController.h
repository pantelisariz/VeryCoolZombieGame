// Copyright University of Inland Norway

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "FPSCharacter.h"
#include "GameFramework/PlayerController.h"
#include "FPSController.generated.h"

/**
 * 
 */
UCLASS()
class ZOMBIEAPOCALYPSE_API AFPSController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AFPSController();
	
protected:
	virtual void SetupInputComponent() override;
	
	virtual void OnPossess(APawn* InPawn) override;
	

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	
	void JumpStart();
	void JumpEnd();
	
	void RunStart();
	void RunEnd();
	
	void FireStart();
	void FireEnd();
	
	void Interact();
	
	void Reload();
	
	virtual void Pause() override;
	

	
	
	
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputMappingContext> CurrentMappingContext;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input|Action", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> MoveAction;	
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input|Action", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> LookAction;	
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input|Action", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> JumpAction;	
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input|Action", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> RunAction;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input|Action", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> FireAction;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input|Action", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> InteractAction;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input|Action", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> ReloadAction;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input|Action", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> PauseAction;
	bool bIsPaused;
	
	
	
	UPROPERTY()
	TObjectPtr<AFPSCharacter> FPSCharacter;
};
