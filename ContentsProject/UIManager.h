#pragma once
#include <EngineCore/Actor.h>

#include "TileMap.h"
#include "MenuPanelUI.h"
#include "Score.h"

enum class UICollisionGroup
{
	Cursor,
	Ground,
	Building,
	Croppatch,
	Panel,
};

static int Money = 400;
static int Bio = 8;
static int BioExchange = 1;

// ���� :
class AUIManager : public AActor
{
public:
	AUIManager();
	~AUIManager();

	AUIManager(const AUIManager& _Other) = delete;
	AUIManager(AUIManager&& _Other) noexcept = delete;
	AUIManager& operator=(const AUIManager& _Other) = delete;
	AUIManager& operator=(AUIManager&& _Other) noexcept = delete;

	void BeginPlay();

	void Tick(float _DeltaTime);

	USpriteRenderer* GetCursorImage()
	{
		return CursorImage;
	}

	void SetMenuPanelUI(AMenuPanelUI* const _MenuPanelUI)
	{
		MenuPanelUI = _MenuPanelUI;
	}

	void TapButtonIn();
	void TapButtonOut();
	void TapButtonStay(AActor* _Actor, FTransform _Index);

	void PanelButtonTileEnter(AActor* _Actor, FTransform _Index);
	void PanelButtonTileStay(AActor* _Actor, FTransform _Index);
	void PanelButtonTileEnd(AActor* _Actor, FTransform _Index);

	void CreateText(AScore* _AScore, FVector2D _Location, int _Value, int _Order = false, bool _Active = true, ERenderOrder _ERenderOrder = ERenderOrder::UIUP)
	{
		if (_AScore != ResourcesText[4])
		{
			_AScore->SetTextSpriteName("Text.png");
		}
		else
		{
			_AScore->SetTextSpriteName("TextGreen.png");
		}
		_AScore->SetOrder(_ERenderOrder);
		_AScore->SetTextScale({ 7.5f, 15.f });
		_AScore->SetActorLocation(_Location);
		_AScore->SetValue(_Value, _Order, _Active);
	}

	ATileMap* GroundTileMap = nullptr;

	std::vector<class Tile*> CropsAllVector;
	USpriteRenderer* CroppatchTileImage[1000] = {};
	ATileMap* CroppatchTile = nullptr;

	std::vector<class Tile*> StorageTilesVector;
	std::vector<class Tile*> WellTilesVector;
	std::vector<int> FarmingStats;

	AScore* ResourcesText[10] = {};
	AScore* CropsCountText[CropsCount] = {};
	AScore* CropsPriceText[CropsCount] = {};

	AMenuPanelUI* MenuPanelUI = nullptr;

	int CropsLock = 2;
protected:

private:
	class U2DCollision* CursorCollision = nullptr;
	class USpriteRenderer* CursorImage = nullptr;

	class USpriteRenderer* SRFarmInfo = nullptr;
	class USpriteRenderer* SRButtonBlack = nullptr;
	class USpriteRenderer* SRTapWhite = nullptr;

	bool CursorOnTap = false;
	int NowSelectCrops = -1;
	int NowSelectTap = 1;
	int TapTimer = 0;

	std::vector<class U2DCollision*> PanelAllVector;
};