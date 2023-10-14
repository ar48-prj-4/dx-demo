#pragma once
#include "IJ_Item.h"


namespace IJ
{
	class Item_Pocket_Light : public Item
	{
	public:
		Item_Pocket_Light();
		virtual ~Item_Pocket_Light();

		void ItemEffect(ya::Player* player);

	private:

	};
}
