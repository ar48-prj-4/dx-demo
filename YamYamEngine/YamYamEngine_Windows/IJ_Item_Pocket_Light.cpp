#include "IJ_Item_Pocket_Light.h"


namespace IJ
{
	Item_Pocket_Light::Item_Pocket_Light()
	{
	}

	Item_Pocket_Light::~Item_Pocket_Light()
	{
	}

	void Item_Pocket_Light::ItemEffect(ya::Player* player)
	{
		int lp = player->GetLightPower();
		lp += 1;
		player->SetLightPower(lp);
	}
}