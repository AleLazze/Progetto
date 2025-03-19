// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerControllerClass.h"
#include "Components/InputComponent.h"

APlayerControllerClass::APlayerControllerClass()
{
	bShowMouseCursor = true;
	bEnableClickEvents = true;
}

void APlayerControllerClass::BeginPlay()
{
	Super::BeginPlay();

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(InputContext, 0);
	}

}

void APlayerControllerClass::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(ClickAction, ETriggerEvent::Triggered, this, &APlayerControllerClass::ClickOnGrid);
	}
}

void APlayerControllerClass::ClickOnGrid()
{
	const auto HumanPlayer = Cast<AHumanPlayer>(GetPawn());
	if (IsValid(HumanPlayer))
	{
		HumanPlayer->OnClick();
	}
}