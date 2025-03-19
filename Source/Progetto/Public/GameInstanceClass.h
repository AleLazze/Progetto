// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GameInstanceClass.generated.h"

/**
 * 
 */
UCLASS()
class PROGETTO_API UGameInstanceClass : public UGameInstance
{
	GENERATED_BODY()
	
public:
	// Shows the current player's turn
	UPROPERTY(EditAnywhere)
	FString CurrentTurnMessage = "Current Player";

	// Returns turn message
	UFUNCTION(BlueprintCallable)
	FString GetCurrentTurnMessage();

	// Sets turn message
	UFUNCTION(BlueprintCallable)
	void SetCurrentTurnMessage(FString Message);



};
