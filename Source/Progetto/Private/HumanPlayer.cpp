// Fill out your copyright notice in the Description page of Project Settings.


#include "HumanPlayer.h"
#include "Tile.h"
#include "GameField.h"
#include "GameModeClass.h"
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

	PlayerNumber = 1;

}

// Called when the game starts or when spawned
void AHumanPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}


void AHumanPlayer::OnTurn()
{
	bIsMyTurn = true;
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
	if (!bIsMyTurn)
	{
		return;
	}

	// Record the hit location
	FHitResult Hit = FHitResult(ForceInit);

	// Get the hit result under the cursor
	GetWorld()->GetFirstPlayerController()->GetHitResultUnderCursor(ECC_Visibility, false, Hit);

	if (Hit.bBlockingHit)
	{
		if (ATile* Tile = Cast<ATile>(Hit.GetActor()))
		{
			if (Tile->GetTileOwner() == -1 && !Tile->bIsObstacle)
			{
				FVector2D SpawnLocation = Tile->GetGridPosition();

				
			}
		}
		


	}
}

