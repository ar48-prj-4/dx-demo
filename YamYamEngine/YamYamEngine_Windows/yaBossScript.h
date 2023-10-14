#pragma once
#include "yaScript.h"

namespace ya
{
	class BossScript : public Script
	{
	public:
		BossScript();
		virtual ~BossScript();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render() override;

		Vector3 GetPosition()
		{
			return mBossPos;
		}

	private:
		Vector3 mBossPos;
	};
}