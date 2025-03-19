// Fill out your copyright notice in the Description page of Project Settings.


#include "GameField.h"

// Sets default values
AGameField::AGameField()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Size of field
	FieldSize = 25;

	// Size of tile
	TileSize = 100.f;

	// Tile padding
	TilePadding = 0.01f;

	// Obstacle percentage
	ObstaclePercentage = 0.1;

	// Create camera component
	GameCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("GameCamera"));
	GameCamera->SetupAttachment(RootComponent);

}

void AGameField::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	// Next cell multiplier
	NextTileMultiplier = (TileSize + TileSize * TilePadding) / TileSize;

	// Set camera location
	if (GameCamera)
	{
		// Get total field size
		float TotalFieldSize = FieldSize * TileSize + (FieldSize - 1) * (TileSize * TilePadding);
		float CameraLocation = TotalFieldSize * 0.5f;
		

		GameCamera->SetWorldLocation(FVector(CameraLocation, CameraLocation, 2500.f));
		GameCamera->SetWorldRotation(FRotator(-90.f, 0.f, 0.f));
	}

	// Debug
	UE_LOG(LogTemp, Warning, TEXT("OnConstruction: Camera Location: X=%f, Y=%f, Z=%f"),
		GameCamera->GetComponentLocation().X,
		GameCamera->GetComponentLocation().Y,
		GameCamera->GetComponentLocation().Z);
}


// Called when the game starts or when spawned
void AGameField::BeginPlay()
{
	Super::BeginPlay();

	// Obtain player controller and set camera view target
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (PlayerController)
	{
		PlayerController->SetViewTarget(this);
	}
	
	GenerateField();

	// Number of obstacles
	int32 NumObstacles = (FieldSize * FieldSize) * ObstaclePercentage;
	GenerateObstacles(NumObstacles);
	
}

void AGameField::GenerateField()
{
	// Clear array of tiles
	Tiles.Empty();
	// Generate field
	for (int32 i = 0; i < FieldSize; i++)
	{
		for (int32 j = 0; j < FieldSize; j++)
		{
			// Store location of the tile
			FVector TileLocation = AGameField::GetRelativeTilePosition(i, j);

			// Create tile
			ATile* Tile = GetWorld()->SpawnActor<ATile>(TileClass, TileLocation, FRotator::ZeroRotator);

			// Set grid position
			const float TileScale = TileSize / 100.f;
			const float ZScale = 0.1;
			Tile->SetActorScale3D(FVector(TileScale, TileScale, ZScale));
			Tile->SetGridPosition(FVector2D(i, j));
			// Add tile to array
			Tiles.Add(Tile);
			// Add tile to map
			TileMap.Add(FVector2D(i, j), Tile);
		}
	}
}

TArray<class ATile*> AGameField::GetTiles()
{
	return Tiles;
}

FVector2D AGameField::GetTilePosition(const FHitResult& Hit)
{
	return Cast<ATile>(Hit.GetActor())->GetGridPosition();
}

FVector AGameField::GetRelativeTilePosition(int32 X, int32 Y)
{
	return FVector(TileSize * NextTileMultiplier * X, TileSize * NextTileMultiplier * Y, 0);
}

void AGameField::GenerateObstacles(int32 NumObstacles)
{
	if (Tiles.Num() == 0)
	{
		// Debug
		UE_LOG(LogTemp, Warning, TEXT("No tiles found"));
		return;
	}

	TArray<ATile*> AvailableTiles = Tiles;
	for (int32 i = 0; i < NumObstacles; i++)
	{
		// Get random tile
		int32 RandomIndex = FMath::RandRange(0, AvailableTiles.Num() - 1);
		ATile* RandomTile = AvailableTiles[RandomIndex];
		// Set tile as obstacle
		RandomTile->SetAsObstacle(ObstacleMaterial);
		// Remove tile from available tiles
		AvailableTiles.RemoveAt(RandomIndex);
	}
}

void AGameField::PlaceUnitOnTile(TSubclassOf<AGameUnit> UnitClass, FVector2D Position, int32 Player)
{
	if (TileMap.Contains(Position) == false)
	{
		// Debug
		UE_LOG(LogTemp, Warning, TEXT("Tile not found"));
		return;
	}


	ATile* TargetTile = TileMap[Position];

	// Check if tile is occupied
	if (TargetTile->GetTileOwner() != -1)
	{
		// Debug
		UE_LOG(LogTemp, Warning, TEXT("Tile is occupied"));
		return;
	}

	// Set spawn location
	FVector SpawnLocation = TargetTile->GetActorLocation();
	SpawnLocation.Z = 100.f;

	AGameUnit* SpawnedUnit = GetWorld()->SpawnActor<AGameUnit>(UnitClass, SpawnLocation, FRotator::ZeroRotator);

	if (SpawnedUnit)
	{
		SpawnedUnit->SetUnitOwner(Player);
		TargetTile->SetTileOwner(Player);
	}	
}