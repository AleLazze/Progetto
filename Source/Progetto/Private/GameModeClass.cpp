// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModeClass.h"


AGameModeClass::AGameModeClass()
{
	FieldSize = 25;
}

void AGameModeClass::BeginPlay()
{
	Super::BeginPlay();

	isGameOver = false;

	TurnCounter = 0;

	// Aggiungo i player quando avrò creato le classi

	// Faccio in modo che HumanPlayer = 0
	// Players.Add(HumanPlayer);
	// 
	// 
	// Aggiungo random player
	// Players.Add(IA);

	this->PickPlayerStartGame();
}

void AGameModeClass::PickPlayerStartGame()
{
	// Pick a random player to start the game
	CurrentPlayer = FMath::RandRange(0, Players.Num() - 1);

	// Start the game
	TurnCounter += 1;
	Players[CurrentPlayer]->OnTurn();
}

int32 AGameModeClass::GetNextPlayer(int32 Player)
{
	// Get the next player
	Player++;
	if (Player >= Players.Num())
	{
		Player = 0;
	}
	return Player;
}

void AGameModeClass::EndTurn()
{
	// End the turn
	CurrentPlayer = GetNextPlayer(CurrentPlayer);
	TurnCounter += 1;
	Players[CurrentPlayer]->OnTurn();
}