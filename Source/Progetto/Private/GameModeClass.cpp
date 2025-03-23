// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModeClass.h"
#include "HumanPlayer.h"
#include "AIPlayer.h"
#include "Kismet/GameplayStatics.h"
#include "EngineUtils.h"


AGameModeClass::AGameModeClass()
{
	FieldSize = 25;
}

void AGameModeClass::BeginPlay()
{
	Super::BeginPlay();

	bIsGameOver = false;

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

	// Add HumanPlayer to the list of players
	Players.Add(HumanPlayer);
	
	// Create the camera
	float TotalFieldSize = FieldSize * GameField->TileSize + (FieldSize - 1) * (GameField->TileSize * GameField->TilePadding);
	float CameraPosition = TotalFieldSize * 0.5;
	float CameraHeight = 2500;
	FVector CameraPos(CameraPosition, CameraPosition, CameraHeight);
	HumanPlayer->SetActorLocationAndRotation(CameraPos, FRotator(-90.f, 0.f, -90.f));
	
	// Add AI players
	AAIPlayer* AIPlayer = GetWorld()->SpawnActor<AAIPlayer>(FVector(), FRotator());

	Players.Add(AIPlayer);

	// Choose first player
	ChoosePlayer();

	// Starts game with placement phase
	StartPlacementPhase();
	
}

void AGameModeClass::ChoosePlayer()
{
	CurrentPlayer = FMath::RandRange(0, Players.Num() - 1);

	Players[CurrentPlayer]->OnTurn();
}

void AGameModeClass::StartPlacementPhase()
{
	bIsPlacementPhase = true;
	bIsGamePhase = false;

}

void AGameModeClass::StartGamePhase()
{
	bIsPlacementPhase = false;
	bIsGamePhase = true;

}

void AGameModeClass::PlaceUnit(int32 Player, FVector Location, TSubclassOf<AGameUnit> UnitClass)
{
	if (Player != CurrentPlayer)
	{
		// Debug
		UE_LOG(LogTemp, Error, TEXT("It's not the turn of player %d"), Player);
		return;
	}

	GetWorld()->SpawnActor<AGameUnit>(UnitClass, Location, FRotator::ZeroRotator);

	NextPlayer();

}

void AGameModeClass::NextPlayer()
{
	CurrentPlayer = 1 - CurrentPlayer;
	Players[CurrentPlayer]->OnTurn();
}