// Fill out your copyright notice in the Description page of Project Settings.


#include "HumanPlayer.h"
#include "Tile.h"
#include "GameField.h"
#include "GameModeClass.h"
#include "Brawler.h"
#include "Sniper.h"
#include "Components/InputComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

// Sets default values
AHumanPlayer::AHumanPlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set this pawn to be controlled by the lowest-numbered player
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	// Create camera component
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(RootComponent);

	// Get game instance
	GameInstance = Cast<UGameInstanceClass>(UGameplayStatics::GetGameInstance(GetWorld()));

	PlayerNumber = -1;

}

// Called when the game starts or when spawned
void AHumanPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}


void AHumanPlayer::OnTurn()
{
	bIsMyTurn = true;
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Human turn!"));
	GameInstance->SetCurrentTurnMessage(TEXT("Human turn!"));
}

void AHumanPlayer::OnWin()
{
	GameInstance->SetCurrentTurnMessage(TEXT("Human wins!"));
}

void AHumanPlayer::OnLose()
{
	GameInstance->SetCurrentTurnMessage(TEXT("Human loses!"));
}

// Called to bind functionality to input
void AHumanPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AHumanPlayer::OnClick()
{
	// Record a hit result
	FHitResult Hit = FHitResult(ForceInit);

	GetWorld()->GetFirstPlayerController()->GetHitResultUnderCursor(ECollisionChannel::ECC_Pawn, false, Hit);
	AGameModeClass* GameMode = Cast<AGameModeClass>(GetWorld()->GetAuthGameMode());

	// Check if it's the placement phase
	if (GameMode->bIsPlacementPhase)
	{
		// Check if it's the player's turn and the hit is valid
		if (bIsMyTurn && Hit.bBlockingHit)
		{
			if (ATile* CurrentTile = Cast<ATile>(Hit.GetActor()))
			{
				// Check if the tile is empty
				if (CurrentTile->TileOwner == -1)
				{
					GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Tile clicked!"));	// Debug
					CurrentTile->SetTileOwner(PlayerNumber);
					FVector SpawnLocation = CurrentTile->GetActorLocation();

					// Check which unit to place
					if (GameMode->UnitsToPlace == 2)
					{
						GameMode->PlaceUnit(PlayerNumber, SpawnLocation, ABrawler::StaticClass());
						GameMode->UnitsToPlace--;
						bIsMyTurn = false;
					}
					else if (GameMode->UnitsToPlace == 1)
					{
						GameMode->PlaceUnit(PlayerNumber, SpawnLocation, ASniper::StaticClass());
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
		}
	}
}

