// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModeClass.h"
#include "HumanPlayer.h"
#include "AIPlayer.h"
#include "Brawler.h"
#include "Sniper.h"
#include "Kismet/GameplayStatics.h"


AGameModeClass::AGameModeClass()
{
	FieldSize = 25;
}

void AGameModeClass::BeginPlay()
{
	Super::BeginPlay();

	isGameOver = false;

	TurnCounter = 0;

	/* AHumanPlayer* HumanPlayer = GetWorld()->GetFirstPlayerController()->GetPawn<AHumanPlayer>();

	if (!IsValid(HumanPlayer))
	{
		UE_LOG(LogTemp, Error, TEXT("No HumanPlayer found!"));
		return;
	}
	*/

	// Creates game field
	if (GameFieldClass != nullptr)
	{
		FVector Origin = FVector(0, 0, 0);
		GameField = GetWorld()->SpawnActor<AGameField>(GameFieldClass, Origin, FRotator::ZeroRotator);
		GameField->FieldSize = FieldSize;
	}
	else
	{
		// Debug
		UE_LOG(LogTemp, Error, TEXT("No GameFieldClass found!"));
	}

	// Debug
	if (!GameField)
	{
		UE_LOG(LogTemp, Error, TEXT("No GameField found in the scene!"));
		return;
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("GameField found successfully!"));
	}

	// Add HumanPlayer to the list of players
	Players.Add(HumanPlayer);

	
	// Add AI players
	// auto* AIPlayer = GetWorld()->SpawnActor<AAIPlayer>(FVector(), FRotator());

	// Players.Add(AIPlayer);



	this->PickPlayerPlaceUnits();
}

void AGameModeClass::PickPlayerPlaceUnits()
{
	if (!GameField)
	{
		// Debug
		UE_LOG(LogTemp, Warning, TEXT("No game field found"));
		return;
	}

	// Pick random player
	FirstPlayer = FMath::RandRange(0, Players.Num() - 1);
	SecondPlayer = GetNextPlayer(FirstPlayer);

	// Place units
	GameField->PlaceUnitOnTile(ABrawler::StaticClass(), FVector2D(0, 0), FirstPlayer);
	UE_LOG(LogTemp, Warning, TEXT("Placed Brawler on tile 0,0"));
	GameField->PlaceUnitOnTile(ABrawler::StaticClass(), FVector2D(24, 24), SecondPlayer);
	UE_LOG(LogTemp, Warning, TEXT("Placed Brawler on tile 24,24"));
	GameField->PlaceUnitOnTile(ASniper::StaticClass(), FVector2D(0, 24), FirstPlayer);
	UE_LOG(LogTemp, Warning, TEXT("Placed Sniper on tile 0,24"));
	GameField->PlaceUnitOnTile(ASniper::StaticClass(), FVector2D(24, 0), SecondPlayer);
	UE_LOG(LogTemp, Warning, TEXT("Placed Sniper on tile 24,0"));

}

int32 AGameModeClass::GetNextPlayer(int32 Player)
{
	// Get the next player
	Player = 1 - Player;
	return Player;
}

void AGameModeClass::EndTurn()
{
	// End the turn
	CurrentPlayer = GetNextPlayer(CurrentPlayer);
	TurnCounter += 1;
	Players[CurrentPlayer]->OnTurn();
}