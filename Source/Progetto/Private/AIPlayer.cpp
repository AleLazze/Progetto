// Fill out your copyright notice in the Description page of Project Settings.


#include "AIPlayer.h"
#include "Brawler.h"
#include "Sniper.h"

// Sets default values
AAIPlayer::AAIPlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	GameInstance = Cast<UGameInstanceClass>(UGameplayStatics::GetGameInstance(GetWorld()));

}

// Called when the game starts or when spawned
void AAIPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAIPlayer::OnTurn()
{
	bIsMyTurn = true;
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("AI turn!"));
	GameInstance->SetCurrentTurnMessage(TEXT("AI turn!"));

	// AI logic for placing units

	// Get all empty tiles
	TArray<ATile*> EmptyTiles;
	AGameModeClass* GameMode = Cast<AGameModeClass>(GetWorld()->GetAuthGameMode());
	for (auto& CurrentTile : GameMode->GameField->GetTiles())
	{
		// Check if the tile is empty
		if (!CurrentTile->bIsObstacle && CurrentTile->GetTileOwner() == -1)
		{
			// Add every empty tile to the array
			EmptyTiles.Add(CurrentTile);
		}
	}

	if (EmptyTiles.Num() > 0)
	{
		int32 RandomIndex = FMath::RandRange(0, EmptyTiles.Num() - 1);
		FVector RandomLocation = GameMode->GameField->GetRelativeTilePosition((EmptyTiles[RandomIndex])->GetGridPosition()[0], (EmptyTiles[RandomIndex])->GetGridPosition()[1]);
		EmptyTiles[RandomIndex]->SetTileOwner(PlayerNumber);
		
		// Check which unit to place
		if (GameMode->UnitsToPlace == 2)
		{
			GameMode->PlaceUnit(PlayerNumber, RandomLocation, ABrawler::StaticClass());
			GameMode->UnitsToPlace--;
			bIsMyTurn = false;
		}
		else if (GameMode->UnitsToPlace == 1)
		{
			GameMode->PlaceUnit(PlayerNumber, RandomLocation, ASniper::StaticClass());
			GameMode->UnitsToPlace--;
			bIsMyTurn = false;
		}
		else
		{
			GameMode->bIsPlacementPhase = false;
			GameMode->bIsGamePhase = true;
		}
	}
}

void AAIPlayer::OnWin()
{
	GameInstance->SetCurrentTurnMessage(TEXT("AI wins!"));
}

void AAIPlayer::OnLose()
{
	// GameInstance->SetCurrentTurnMessage(TEXT("AI loses!"));
}

// Called to bind functionality to input
void AAIPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

