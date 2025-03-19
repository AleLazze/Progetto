// Fill out your copyright notice in the Description page of Project Settings.


#include "HumanPlayer.h"
#include "GameField.h"
#include "GameModeClass.h"
#include "Components/InputComponent.h"

// Sets default values
AHumanPlayer::AHumanPlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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
	// Record the hit location
	FHitResult Hit = FHitResult(ForceInit);

	// Get the hit result under the cursor
	GetWorld()->GetFirstPlayerController()->GetHitResultUnderCursor(ECC_Visibility, false, Hit);

	if (Hit.bBlockingHit && bIsMyTurn)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("clicked"));

		// Checks if tile has unit
		if (ATile* CurrentTile = Cast<ATile>(Hit.GetActor()))
		{
			// Checks if current player owns the clicked tile
			if (CurrentTile->GetOwner() == this)
			{
				
			}
		}

	}
}

