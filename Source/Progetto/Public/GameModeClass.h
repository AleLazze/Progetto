// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameField.h"
#include "PlayerInterface.h"
#include "GameFramework/GameModeBase.h"
#include "GameModeClass.generated.h"

/**
 * 
 */
UCLASS()
class PROGETTO_API AGameModeClass : public AGameModeBase
{
	GENERATED_BODY()

public:
	// Is the game over?
	bool bIsGameOver;
	//Array of player interfaces
	TArray<class IPlayerInterface*> Players;
	// Turn counter
	int32 TurnCounter;
	// Current player
	int32 CurrentPlayer;

	// Parameters to keep track of game phases
	bool bIsPlacementPhase = false;
	bool bIsGamePhase = false;

	int32 UnitsToPlace; // Number of units to place per player

	void ChoosePlayer();

	void StartPlacementPhase();
	void StartGamePhase();

	// Function to place a unit on the field
	void PlaceUnit(int32 Player, FVector Location, TSubclassOf<class AGameUnit> UnitClass);
	

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AGameField> GameFieldClass;

	// Field size
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 FieldSize;

	// Reference to the game field
	UPROPERTY(VisibleAnywhere)
	AGameField* GameField;

	AGameModeClass();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void NextPlayer();
	
	
};
