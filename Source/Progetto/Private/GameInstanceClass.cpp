// Fill out your copyright notice in the Description page of Project Settings.


#include "GameInstanceClass.h"

FString UGameInstanceClass::GetCurrentTurnMessage()
{
	return CurrentTurnMessage;
}

void UGameInstanceClass::SetCurrentTurnMessage(FString Message)
{
	CurrentTurnMessage = Message;
}