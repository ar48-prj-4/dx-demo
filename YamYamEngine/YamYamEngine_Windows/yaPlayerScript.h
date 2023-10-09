#pragma once
#include "yaScript.h"

namespace ya
{

	class PlayerScript : public Script
	{
	public:
		PlayerScript();
		virtual ~PlayerScript();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render() override;

		Vector3 GetPosition()
		{
			return mPlayerPos;
		}

	private:
		Vector3 mPlayerPos;
	};

}
