// Fill out your copyright notice in the Description page of Project Settings.


#include "AIPlayer.h"

// Sets default values
AAIPlayer::AAIPlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAIPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAIPlayer::OnTurn()
{
	GameInstance->SetCurrentTurnMessage(TEXT("AI turn!"));
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

