// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GameField.h"
#include "PlayerInterface.h"
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
	bool isGameOver;
	//Array of player interfaces
	TArray<class IPlayerInterface*> Players;
	// Current player
	int32 CurrentPlayer;
	// Turn counter
	int32 TurnCounter;

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

	// Called at the start of the game
	void PickPlayerStartGame();

	// Get next player
	int32 GetNextPlayer(int32 Player);

	// Called at the end of the turn
	void EndTurn();
	
};
