#include "yaLight_TimeLimit.h"
#include "yaTime.h"


namespace ya
{
	Light_TimeLimit::Light_TimeLimit(float light_range, float duration)
		: Light(light_range)
		, m_LifeTime(0.0f)
		, m_Duration(duration)
	{
		ButtonConnectedObject::SetBCOState(eBCOState::Activated);
	}

	void Light_TimeLimit::Update()
	{
		Light::Update();

		m_LifeTime += Time::DeltaTime();
		if (m_LifeTime >= m_Duration)
			Destroy(this);
	}
}