#include "yaMesh.h"
#include "yaRenderer.h"

namespace ya
{
    Mesh::Mesh()
    {
    }

    Mesh::~Mesh()
    {
    }

    HRESULT Mesh::Load(const std::filesystem::path& path)
    {
        return Refresh();
    }

    bool Mesh::CreateVertexBuffer(void* data, UINT Count)
    {
        mVBDesc.ByteWidth = sizeof(renderer::Vertex) * Count;
        mVBDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_VERTEX_BUFFER;
        mVBDesc.Usage = D3D11_USAGE_DEFAULT;
        mVBDesc.CPUAccessFlags = 0;

        D3D11_SUBRESOURCE_DATA subData = {};
        subData.pSysMem = data;

        if (!(GetDevice()->CreateBuffer(&mVBDesc, &subData, mVertexBuffer.ReleaseAndGetAddressOf())))
            return false;

        return true;
    }

    bool Mesh::CreateIndexBuffer(void* data, UINT Count)
    {
        mIndexCount = Count;
        mIBDesc.ByteWidth = sizeof(UINT) * Count;
        mIBDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_INDEX_BUFFER;
        mIBDesc.Usage = D3D11_USAGE_DEFAULT;
        mIBDesc.CPUAccessFlags = 0;

        D3D11_SUBRESOURCE_DATA subData = {};
        subData.pSysMem = data;

        if (!(GetDevice()->CreateBuffer(&mIBDesc, &subData, mIndexBuffer.ReleaseAndGetAddressOf())))
            return false;

        return true;
    }

    void Mesh::BindBuffer()
    {
        UINT stride = sizeof(renderer::Vertex);
        UINT offset = 0;

        GetDevice()->BindVertexBuffer(0, 1, mVertexBuffer.GetAddressOf(), stride, offset);
        GetDevice()->BindIndexBuffer(mIndexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
    }

    void Mesh::Render()
    {
        BindBuffer();

        GetDevice()->DrawIndexed(mIndexCount, 0, 0);
    }

    HRESULT Mesh::Refresh()
    {
        if (CreateVertexBuffer(SetVertexData(), SetVertexCount()) && CreateIndexBuffer(SetIndexData(), SetIndexCount()))
        {
	        return S_OK;
        }

        return E_FAIL;
    }
}
