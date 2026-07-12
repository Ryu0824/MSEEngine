#include "pch.h"
#include "DirectX11Buffer.h"

namespace MSE
{
	extern Microsoft::WRL::ComPtr<ID3D11Device> g_Device;
	extern Microsoft::WRL::ComPtr<ID3D11DeviceContext> g_DeviceContext;


	DirectX11VertexBuffer::DirectX11VertexBuffer(float* vertices, uint32_t size)
	{
		D3D11_BUFFER_DESC bd = {};
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = size;
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;

		D3D11_SUBRESOURCE_DATA initData = {};
		initData.pSysMem = vertices;

		g_Device->CreateBuffer(&bd, &initData, &m_Buffer);
	}

	void DirectX11VertexBuffer::Bind() const
	{
		UINT Stride = m_Layout.GetStride();
		UINT offset = 0;
		g_DeviceContext->IASetVertexBuffers(0, 1, m_Buffer.GetAddressOf(), &Stride, &offset);
	}

	void DirectX11VertexBuffer::Unbind() const
	{
	}

	DirectX11IndexBuffer::DirectX11IndexBuffer(uint32_t* indices, uint32_t count)
		:m_Count(count)
	{
		D3D11_BUFFER_DESC bd = {};
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = count * sizeof(uint32_t);
		bd.BindFlags = D3D11_BIND_INDEX_BUFFER;

		D3D11_SUBRESOURCE_DATA initData = {};
		initData.pSysMem = indices;

		g_Device->CreateBuffer(&bd, &initData, &m_Buffer);
	}

	void DirectX11IndexBuffer::Bind() const
	{
		g_DeviceContext->IASetIndexBuffer(m_Buffer.Get(), DXGI_FORMAT_R32_UINT, 0);
	}

	void DirectX11IndexBuffer::Unbind() const
	{
	}
}
