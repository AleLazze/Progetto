// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayerInterface.h"
#include "GameInstanceClass.h"
#include "GameModeClass.h"
#include "Kismet/GameplayStatics.h"
#include "AIPlayer.generated.h"

UCLASS()
class PROGETTO_API AAIPlayer : public APawn, public IPlayerInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AAIPlayer();

	UGameInstanceClass* GameInstance;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	bool bIsMyTurn = false;

public:
	void OnTurn() override;
	void OnWin() override;
	void OnLose() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
