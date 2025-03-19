// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameUnit.generated.h"

UCLASS()
class PROGETTO_API AGameUnit : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGameUnit();

	// Stats for the unit
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	int32 Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	int32 AttackMin;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	int32 AttackMax;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	int32 AttackRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	int32 MovementRange;

	// Owner functions
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 UnitOwner;

	void SetUnitOwner(int32 Player);

	int32 GetUnitOwner();

	// State of turn
	bool bHasMoved;
	bool bHasAttacked;

	// Function to move the unit and attack
	UFUNCTION(BlueprintCallable, Category = "Actions")
	void Move(FVector TargetLocation);

	UFUNCTION(BlueprintCallable, Category = "Actions")
	void Attack(AGameUnit* TargetUnit);

	UFUNCTION(BlueprintCallable, Category = "Actions")
	void TakeDamage(int32 Damage);

	UFUNCTION(BlueprintCallable, Category = "Actions")
	bool CanMove() const;

	UFUNCTION(BlueprintCallable, Category = "Actions")
	bool CanAttack() const;



	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	// Mesh component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* UnitMesh;


};
