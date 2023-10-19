#pragma once
#include "IJ_Item.h"


namespace IJ
{
	class Item_Heal : public Item
	{
	public:
		Item_Heal();
		virtual ~Item_Heal();

		void ItemEffect(ya::Player* player);

		int GetHealPoint() { return m_heal_point; }
		void SetHealPoint(int heal) { m_heal_point = heal; }

	private:
		int m_heal_point;
	};
}
