#include "yaCamera.h"
#include "yaCamera.h"
#include "yaApplication.h"
#include "yaConstantBuffer.h"
#include "yaTransform.h"
#include "yaInput.h"
#include "yaRenderer.h"
#include "yaTime.h"

extern ya::Application application;

void ya::Camera::Initialize()
{
	// LookAtLH���� z �� 0�� ���� ����
	mLookPosition = Vector3::Forward;
	mPosition = Vector3{0, 0, -2};
}

void ya::Camera::Update()
{
	mWorldMatrix = XMMatrixIdentity();
	mProjectionMatrix = XMMatrixPerspectiveFovLH(DirectX::XM_PI / 2, application.GetWidth() / application.GetHeight(),
	                                             0.1f, 1000.f);

	XMVECTOR upVector = XMLoadFloat3(&Vector3::Up);
	XMVECTOR lookAtVector = XMLoadFloat3(&mLookPosition);
	XMVECTOR positionVector = XMLoadFloat3(&mPosition);

	if (mGameObject != nullptr)
	{
		auto object_pos = mGameObject->GetComponent<Transform>()->GetPosition();
		object_pos.z = -2;
		positionVector = XMLoadFloat3(&object_pos);
	}

	// ����Ͼ� ������ ȸ�� ����� ����
	const XMMATRIX rotationMatrix = XMMatrixRotationQuaternion(mRotation);

	// ȸ�� ����� �̿��ؼ� ȸ���� ī�޶��� �ٶ󺸴� ����� ���� ����
	lookAtVector = XMVector3TransformCoord(lookAtVector, rotationMatrix);
	upVector = XMVector3TransformCoord(upVector, rotationMatrix);

	// �ٶ󺸴� ��ġ�� ī�޶� ��ġ�� ����
	lookAtVector = XMVectorAdd(positionVector, lookAtVector);

	// ī�޶� ���� ����� �� ����� ����
	mViewMatrix = XMMatrixLookAtLH(positionVector, lookAtVector, upVector);

	SetConstantBuffer();
}

void ya::Camera::SetConstantBuffer()
{
	graphics::ConstantBuffer* cb = renderer::constantBuffers[(UINT)graphics::eCBType::Perspective];

	// DirectX 11�� XMMATRIX�� Transpose�ؼ� �Ѱ��־�� ��
	renderer::PerspectiveCB data{
		XMMatrixTranspose(mWorldMatrix),
		XMMatrixTranspose(mViewMatrix),
		XMMatrixTranspose(mProjectionMatrix),
	};

	cb->SetData(&data);

	cb->Bind(graphics::eShaderStage::VS);
}