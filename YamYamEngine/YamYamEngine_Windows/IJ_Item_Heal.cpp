#include "IJ_Item_Heal.h"


namespace IJ
{
	Item_Heal::Item_Heal()
		: m_heal_point(20)
	{
	}

	Item_Heal::~Item_Heal()
	{
	}

	void Item_Heal::ItemEffect(ya::Player* player)
	{
		int hp = player->GetHP();
		hp += m_heal_point;
		player->SetHP(hp);
	}
}