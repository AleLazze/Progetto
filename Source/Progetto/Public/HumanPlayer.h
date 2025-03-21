// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GameInstanceClass.h"
#include "PlayerInterface.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "HumanPlayer.generated.h"

UCLASS()
class PROGETTO_API AHumanPlayer : public APawn, public IPlayerInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AHumanPlayer();

	// Camera attached to the player
	UCameraComponent* Camera;

	UGameInstanceClass* GameInstance;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Track turn
	bool bIsMyTurn = false;

	// Track if player is placing units
	bool bIsPlacingUnits = false;
	int32 UnitsPlaced = 0;

	// Unit to place
	TSubclassOf<class AGameUnit> SelectedUnitToPlace;
	// Game field
	class AGameField* GameField;

public:	
	void OnTurn() override;
	void OnWin() override;
	void OnLose() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Called on left mouse click
	UFUNCTION()
	void OnClick();
};
