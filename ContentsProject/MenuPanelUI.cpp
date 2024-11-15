#include "PreCompile.h"
#include "MenuPanelUI.h"

AMenuPanelUI::AMenuPanelUI()
{
	Location.X = ScreenX - 256 + 22;
	Location.Y = ScreenHY + 93;

	{
		Sprite[index] = CreateDefaultSubObject<USpriteRenderer>();
		Sprite[index]->SetComponentCrate(Sprite[index], "000_MenuPanel.png", {}, { Location.X, Location.Y }, ERenderOrder::UI);
		++index;
	}

	{
		Sprite[index] = CreateDefaultSubObject<USpriteRenderer>();
		Sprite[index]->SetComponentCrate(Sprite[index], "001_MenuPanel.png", { 1, 1 }, { Location.X - 256 + 5, static_cast<float>(Location.Y - 2) }, ERenderOrder::UI);
		++index;
	}

	{
		Sprite[index] = CreateDefaultSubObject<USpriteRenderer>();
		Sprite[index]->SetComponentCrate(Sprite[index], "002_MenuPanel.png", { 1, 1 }, { Location.X + 1, Location.Y - 1 }, ERenderOrder::UI);
		++index;
	}

	{
		Sprite[index] = CreateDefaultSubObject<USpriteRenderer>();
		Sprite[index]->SetComponentCrate(Sprite[index], "003_MenuPanel.png", {}, { Location.X + 1, (Location.Y + 126) }, ERenderOrder::UIUP);
		++index;
	}

	{
		Sprite[index] = CreateDefaultSubObject<USpriteRenderer>();
		Sprite[index]->SetComponentCrate(Sprite[index], "003_MenuPanel_Font.png", {32 , 16}, { Location.X + 103, static_cast<float>((Location.Y + 130)) }, ERenderOrder::UIUP);
		++index;
	}

	{
		int Loc = 0;
		int Loc2 = 0;
		for (size_t i = 0; i < 44; ++i)
		{
			//ö�� ��ư
			if (3 == i)
			{
				Loc = 0;
				Loc2 = 1;
			}
			else if (4 == i)
			{
				Loc2 = 0;
			}
			else if (42 == i)
			{
				Loc = 0;
				Loc2 = 1;
			}
			else if (43 == i)
			{
				Loc2 = 0;
			}

			//SpriteRFarmSlot[i] = CreateDefaultSubObject<USpriteRenderer>();
			//SpriteRFarmSlot[i]->SetComponentCrate(SpriteRFarmSlot[i], "000_crop-seed-button.png", {}, { (Location.X - 153 + (Loc * 104)), (Location.Y - 120 + ((Loc / 4) + ((i / 4) + Loc2)) * 46) }, ERenderOrder::UI);

			if (i > (24 - 1))
			{
				//SpriteRFarmSlot[i]->SetActive(false);
			}

			++Loc;
			if (4 <= Loc)
			{
				Loc = 0;
			}
		}

		Loc = 0;
		Loc2 = 0;
		for (size_t i = 44; i < 48; ++i)
		{
			SpriteRFarmSlot[i] = CreateDefaultSubObject<USpriteRenderer>();
			SpriteRFarmSlot[i]->SetComponentCrate(SpriteRFarmSlot[i], "001_crop-seed-button.png", { 51, 51 }, { (Location.X - 170 + (3 * 104) + (Loc * 53)), (Location.Y - 116 + (Loc / 5 * 53)) }, ERenderOrder::UI);;

			++Loc;
			if (46 == i)
			{
				Loc2 = 11;
			}
		}

	}
}

AMenuPanelUI::~AMenuPanelUI() 
{
}

