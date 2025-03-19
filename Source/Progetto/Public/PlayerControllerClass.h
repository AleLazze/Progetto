// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "HumanPlayer.h"
#include "InputActionValue.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "PlayerControllerClass.generated.h"

/**
 * 
 */
UCLASS()
class PROGETTO_API APlayerControllerClass : public APlayerController
{
	GENERATED_BODY()

public:
	APlayerControllerClass();

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputMappingContext* InputContext;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* ClickAction;

	void ClickOnGrid();

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
};
