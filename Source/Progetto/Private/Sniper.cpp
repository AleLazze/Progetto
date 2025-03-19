// Fill out your copyright notice in the Description page of Project Settings.


#include "Sniper.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Materials/MaterialInstanceDynamic.h"


ASniper::ASniper()
{
	Health = 20;
	AttackMin = 4;
	AttackMax = 8;
	AttackRange = 10;
	MovementRange = 3;

}



