#pragma once
#include "yaScript.h"
#include "yaPlayerScript.h"
#include "yaTurretScript.h"

namespace ya
{
	class BulletScript : public Script
	{
	public:
		BulletScript();
		virtual ~BulletScript();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render() override;
		
		Vector3 GetPosition()
		{
			return mBulletPos;
		}

	private:
		Vector3 mBulletPos;
		PlayerScript* playerSC;
	};
}
