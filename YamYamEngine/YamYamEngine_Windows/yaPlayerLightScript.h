#pragma once
#include "yaScript.h"


namespace ya
{
	class PlayerLightScript : public Script
	{
	public:
		PlayerLightScript();
		virtual ~PlayerLightScript();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render() override;

	private:

	};
}
