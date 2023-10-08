#include "yaRenderer.h"
#include "yaApplication.h"
#include "yaResources.h"
#include "yaSquareMesh.hpp"
#include "yaTriangleMesh.hpp"

extern ya::Application application;

namespace ya::renderer
{
	D3D11_INPUT_ELEMENT_DESC InputLayouts[3];
	ConstantBuffer* constantBuffers[(UINT)graphics::eCBType::End];

	Microsoft::WRL::ComPtr<ID3D11SamplerState> PSSamplerState;
	
	void SetUpStates()
	{
		GetDevice()->CreateSampler(PSSamplerState.GetAddressOf());
		GetDevice()->BindSampler(PSSamplerState.Get(), eShaderStage::PS);
	}

	void LoadBuffer()
	{
		Resources::Insert<Mesh>(L"TriangleMesh", new TriangleMesh());
		Resources::Insert<Mesh>(L"SquareMesh", new SquareMesh());
		Resources::Insert<Texture>(L"Texture", new Texture(L"Texture", L"../Resources/Textures/Texture.png"));
		
		constantBuffers[(UINT)graphics::eCBType::Transform] = new ConstantBuffer(eCBType::Transform);
		constantBuffers[(UINT)graphics::eCBType::Transform]->Create(sizeof(TransformCB));

		constantBuffers[(UINT)graphics::eCBType::Perspective] = new ConstantBuffer(eCBType::Perspective);
		constantBuffers[(UINT)graphics::eCBType::Perspective]->Create(sizeof(PerspectiveCB));
	}

	void LoadShader()
	{
		const auto colorShader = new Shader();
		colorShader->Create(eShaderStage::VS, L"TriangleVS.hlsl", "VS_Test");
		colorShader->Create(eShaderStage::PS, L"TrianglePS.hlsl", "PS_Test");
		Resources::Insert(L"ColorShader", colorShader);

		const auto textureShader = new Shader();
		textureShader->Create(eShaderStage::VS, L"TriangleVS.hlsl", "VS_Test");
		textureShader->Create(eShaderStage::PS, L"TexturePS.hlsl", "PS_Test");
		Resources::Insert(L"TextureShader", textureShader);

		// Input layout ���� ���� ����, �� ���̴� ��� ���� �Է� ������ ����ϹǷ� �ѹ��� ����
		InputLayouts[0].AlignedByteOffset = 0;
		InputLayouts[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
		InputLayouts[0].InputSlot = 0;
		InputLayouts[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		InputLayouts[0].SemanticName = "POSITION";
		InputLayouts[0].SemanticIndex = 0;

		InputLayouts[1].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
		InputLayouts[1].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		InputLayouts[1].InputSlot = 0;
		InputLayouts[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		InputLayouts[1].SemanticName = "COLOR";
		InputLayouts[1].SemanticIndex = 0;

		InputLayouts[2].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
		InputLayouts[2].Format = DXGI_FORMAT_R32G32_FLOAT;
		InputLayouts[2].InputSlot = 0;
		InputLayouts[2].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		InputLayouts[2].SemanticName = "TEXCOORD";
		InputLayouts[2].SemanticIndex = 0;

		GetDevice()->CreateInputLayout(InputLayouts, 3,
			colorShader->GetVSCode()->GetBufferPointer()
			, colorShader->GetVSCode()->GetBufferSize()
			, colorShader->GetInputLayoutAddressOf());

		GetDevice()->CreateInputLayout(InputLayouts, 3,
			textureShader->GetVSCode()->GetBufferPointer()
			, textureShader->GetVSCode()->GetBufferSize()
			, textureShader->GetInputLayoutAddressOf());
	}

	void Initialize()
	{
		LoadShader();
		SetUpStates();
		LoadBuffer();
	}

	void Release()
	{
		delete constantBuffers[(UINT)graphics::eCBType::Transform];
		delete constantBuffers[(UINT)graphics::eCBType::Perspective];
	}
}