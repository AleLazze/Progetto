// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModeClass.h"
#include "HumanPlayer.h"
#include "AIPlayer.h"
#include "Brawler.h"
#include "Sniper.h"
#include "Kismet/GameplayStatics.h"
#include "EngineUtils.h"


AGameModeClass::AGameModeClass()
{
	FieldSize = 25;
}

void AGameModeClass::BeginPlay()
{
	Super::BeginPlay();

	isGameOver = false;

	TurnCounter = 0;

	AHumanPlayer* HumanPlayer = GetWorld()->GetFirstPlayerController()->GetPawn<AHumanPlayer>();

	// Debug
	if (!IsValid(HumanPlayer))
	{
		UE_LOG(LogTemp, Error, TEXT("No player pawn of type '%s' was found."), *AHumanPlayer::StaticClass()->GetName());
		return;
	}
	

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
	
	// Create the camera
	float TotalFieldSize = FieldSize * GameField->TileSize + (FieldSize - 1) * (GameField->TileSize * GameField->TilePadding);
	float CameraPosition = TotalFieldSize * 0.5;
	float CameraHeight = 2500;
	FVector CameraPos(CameraPosition, CameraPosition, CameraHeight);
	HumanPlayer->SetActorLocationAndRotation(CameraPos, FRotationMatrix::MakeFromX(FVector(0, 0, -1)).Rotator());

	// Debug
	UE_LOG(LogTemp, Warning, TEXT("OnConstruction: Camera Location: X=%f, Y=%f, Z=%f"),
		HumanPlayer->Camera->GetComponentLocation().X,
		HumanPlayer->Camera->GetComponentLocation().Y,
		HumanPlayer->Camera->GetComponentLocation().Z);

	
	// Add AI players
	AAIPlayer* AIPlayer = GetWorld()->SpawnActor<AAIPlayer>(FVector(), FRotator());

	Players.Add(AIPlayer);



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