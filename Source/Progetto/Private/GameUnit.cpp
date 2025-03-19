// Fill out your copyright notice in the Description page of Project Settings.


#include "GameUnit.h"

// Sets default values
AGameUnit::AGameUnit()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Creates mesh component
	UnitMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("UnitMesh"));
	RootComponent = UnitMesh;

	// Debug
	UE_LOG(LogTemp, Warning, TEXT("AGameUnit created with RootComponent set"));

}

// Function to set the player owner
void AGameUnit::SetUnitOwner(int32 Player)
{
	UnitOwner = Player;
}

// Function to get the player owner
int32 AGameUnit::GetUnitOwner()
{
	return UnitOwner;
}

// Function to move the unit
void AGameUnit::Move(FVector TargetLocation)
{
	if (bHasMoved)
	{
		return;
	}

	float Distance = FVector::Distance(GetActorLocation(), TargetLocation);
	if (Distance > MovementRange * 100.f)
	{
		return;
	}

	SetActorLocation(TargetLocation);
	bHasMoved = true;
	return;
}

// Function to attack another unit
void AGameUnit::Attack(AGameUnit* TargetUnit)
{
	if (bHasAttacked || !TargetUnit)
	{
		return;
	}

	float Distance = FVector::Distance(GetActorLocation(), TargetUnit->GetActorLocation());
	if (Distance > AttackRange * 100.f)
	{
		return;
	}

	int32 Damage = FMath::RandRange(AttackMin, AttackMax);
	TargetUnit->TakeDamage(Damage);
	bHasAttacked = true;
	return;
}

// Function to take damage
void AGameUnit::TakeDamage(int32 Damage)
{
	Health -= Damage;
	if (Health <= 0)
	{
		// Destroy();
		UE_LOG(LogTemp, Warning, TEXT("Unit %s has been destroyed"), *GetName());
	}
}

// Function to check if the unit can move
bool AGameUnit::CanMove() const
{
	return !bHasMoved;
}

// Function to check if the unit can attack
bool AGameUnit::CanAttack() const
{
	return !bHasAttacked;
}

// Called when the game starts or when spawned
void AGameUnit::BeginPlay()
{
	Super::BeginPlay();
	
	if (UnitMesh)
	{
		UnitMesh->SetVisibility(true);
		UnitMesh->SetHiddenInGame(false);
		UnitMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	UE_LOG(LogTemp, Warning, TEXT("Unit %s spawned and set visible"), *GetName());
}

