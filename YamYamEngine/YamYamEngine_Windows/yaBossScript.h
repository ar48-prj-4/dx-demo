#pragma once
#include "yaScript.h"
#include "yaPlayerScript.h"

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
		static Vector3 mBossPos;
		Vector3 mPlayerPos;
		Vector3 mBossOrbit;
		PlayerScript* mPlayerSC;
	};
}