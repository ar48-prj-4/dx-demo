#pragma once
#include "yaLight.h"


namespace ya
{
	class Light_TimeLimit : public Light
	{
	public:
		Light_TimeLimit(float light_range, float duration = 5.0f);
		virtual ~Light_TimeLimit() override = default;

		void Update() override;

		void SetDuration(float duration) { m_Duration = duration; }
		float GetDuration() { return m_Duration; }

	private:
		float m_LifeTime;
		float m_Duration;
	};
}
