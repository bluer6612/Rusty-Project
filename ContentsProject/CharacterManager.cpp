#include "PreCompile.h"
#include "CharacterManager.h"

ACharacterManager::ACharacterManager()
{
}

ACharacterManager::~ACharacterManager()
{
}

void ACharacterManager::BeginPlay()
{
	Super::BeginPlay();
}

void ACharacterManager::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

Tile* FindTile(FVector2D _Location)
{
	Tile* CropTile = nullptr;



	return CropTile;
}

void Watering(FVector2D _Location)
{

}