// Fill out your copyright notice in the Description page of Project Settings.


#include "Tile.h"

// Sets default values
ATile::ATile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));

	SetRootComponent(SceneComponent);
	StaticMeshComponent->SetupAttachment(SceneComponent);

	GridPosition = FVector2D(0, 0);

	TileOwner = -1;

	bIsObstacle = false;

}

void ATile::SetTileOwner(int32 Player)
{
	TileOwner = Player;
}

int32 ATile::GetTileOwner()
{
	return TileOwner;
}

void ATile::SetGridPosition(FVector2D Position)
{
	GridPosition = Position;
}

FVector2D ATile::GetGridPosition()
{
	return GridPosition;
}



// Called when the game starts or when spawned
void ATile::BeginPlay()
{
	Super::BeginPlay();
	
}


void ATile::SetAsObstacle(UMaterialInterface* ObstacleMaterial)
{
	bIsObstacle = true;
	if (ObstacleMaterial)
	{
		StaticMeshComponent->SetMaterial(0, ObstacleMaterial);
	}
}