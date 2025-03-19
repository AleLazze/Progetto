// Fill out your copyright notice in the Description page of Project Settings.


#include "Brawler.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Materials/MaterialInstanceDynamic.h"


ABrawler::ABrawler()
{
	Health = 40;
	AttackMin = 1;
	AttackMax = 6;
	AttackRange = 1;
	MovementRange = 6;

}

