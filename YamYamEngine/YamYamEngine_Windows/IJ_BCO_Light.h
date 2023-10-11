#pragma once
#include "IJ_ButtonConnectedObject.h"
#include "yaLighting.h"


namespace IJ
{
	class BCO_Light : public ButtonConnectedObject
	{
	public:
		BCO_Light(float light_range);
		~BCO_Light() override = default;

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render() override;

		void OnCollisionEnter(ya::Collider* other) override;
		void OnCollisionStay(ya::Collider* other) override;
		void OnCollisionExit(ya::Collider* other) override;

		float GetLightRange() const { return m_light_range_; }

		const std::vector<ya::Lighting*>& GetLightings() const { return m_lightings_; }

	private:
		friend class Lighting;

		std::vector<ya::Lighting*> m_lightings_;
		float m_light_range_;
	};
}
