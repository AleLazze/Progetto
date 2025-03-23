// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Camera/CameraComponent.h"
#include "Tile.h"
#include "GameUnit.h"
#include "GameField.generated.h"

UCLASS()
class PROGETTO_API AGameField : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGameField();

	// Called when an instance of this class is placed (in editor) or spawned
	virtual void OnConstruction(const FTransform& Transform) override;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Generate an empty field
	void GenerateField();

	// Return array of tiles
	TArray<class ATile*> GetTiles();

	// Return tile position on hit
	FVector2D GetTilePosition(const FHitResult& Hit);

	// Get relative position of tile given x and y
	FVector GetRelativeTilePosition(int32 X, int32 Y);

	// Generate obstacles
	void GenerateObstacles(int32 NumObstacles);


	// Size of field
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 FieldSize;

	// Size of tile
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float TileSize;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float TilePadding;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float NextTileMultiplier;

	// Array of tiles
	UPROPERTY(Transient)
	TArray<class ATile*> Tiles;

	// Map of tiles
	UPROPERTY(Transient)
	TMap<FVector2D, ATile*> TileMap;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ATile> TileClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Obstacles")
	UMaterialInterface* ObstacleMaterialTree;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Obstacles")
	UMaterialInterface* ObstacleMaterialRock;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Obstacles")
	float ObstaclePercentage;


};
