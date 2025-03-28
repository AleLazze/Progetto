// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tile.generated.h"

UCLASS()
class PROGETTO_API ATile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATile();

	void SetTileOwner(int32 Player);

	int32 GetTileOwner();

	void SetGridPosition(FVector2D Position);

	FVector2D GetGridPosition();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Set obstacle
	void SetAsObstacle(UMaterialInterface* ObstacleMaterial);


	// Scene component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USceneComponent* SceneComponent;

	// Static mesh component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* StaticMeshComponent;

	// Player that owns the tile
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 TileOwner;

	// Position of the tile in the grid
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FVector2D GridPosition;

	// Check if tile is obstacle
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bIsObstacle;

};
