// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameUnit.h"
#include "Sniper.generated.h"

/**
 Sniper class that inherits from GameUnit
 Parameters are set in the constructor
 */
UCLASS(Blueprintable)
class PROGETTO_API ASniper : public AGameUnit
{
	GENERATED_BODY()
	

public:
	ASniper();

};
