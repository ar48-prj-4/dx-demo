#pragma once
#include "yaGameObject.h"

namespace ya
{
	class Camera
	{
	public:
		static void Initialize();
		static void Update();

		// ī�޶��� ��ġ, z ������ ī�޶� �յڷ� �̵���ų �� ����
		static void SetPosition(const Vector3& position) { mPosition = position; }
		// ī�޶��� ȸ��
		static void SetRotation(const Quaternion& rotation) { mRotation = rotation; }
		// ī�޶� �ٶ󺸴� ����
		static void SetLookPosition(const Vector3& position) { mLookPosition = position; }
		// ��ô�ϴ� ������Ʈ, ������ ��� ī�޶��� ��ġ�� ������Ʈ�� ����
		static void SetTarget(GameObject* gameObject) { mGameObject = gameObject; }
		// ������Ʈ ������ �ߴ��ϰ� ī�޶��� ��ġ�� �ǵ��ư�.
		static void ResetTarget() { mGameObject = nullptr; }

	private:
		// ���� ī�޶� �Ķ���͸� ��� ���۷� ���ε�
		static void SetConstantBuffer();

		inline static GameObject* mGameObject{};

		inline static Vector3 mLookPosition{};	
		inline static Vector3 mPosition{};
		inline static Quaternion mRotation{};

		// ī�޶� �۷ι� ������ �߽���
		inline static XMMATRIX mWorldMatrix{};
		// ȭ�鿡 ���� ���� ���
		inline static XMMATRIX mProjectionMatrix{};
		// ī�޶��� ��ġ, ȸ���� ���� �� ���
		inline static XMMATRIX mViewMatrix{};
	};
}


