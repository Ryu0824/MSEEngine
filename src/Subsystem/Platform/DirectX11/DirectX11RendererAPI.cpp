#include "pch.h"
#include "DirectX11RendererAPI.h"
#include <d3d11.h>
#include <wrl/client.h>

namespace MSE
{
	extern Microsoft::WRL::ComPtr<ID3D11DeviceContext> g_DeviceContext;
	extern Microsoft::WRL::ComPtr<ID3D11RenderTargetView> g_RenderTargetView;

	void DirectX11RendererAPI::SetClearColor(const float color[4])
	{
		m_ClearColor[0] = color[0];
		m_ClearColor[1] = color[1];
		m_ClearColor[2] = color[2];
		m_ClearColor[3] = color[3];
	}

	void DirectX11RendererAPI::Clear()
	{
		g_DeviceContext->ClearRenderTargetView(g_RenderTargetView.Get(), m_ClearColor);
	}

	void DirectX11RendererAPI::DrawIndexed(const std::shared_ptr<IndexBuffer>& indexBuffer)
	{
		g_DeviceContext->DrawIndexed(indexBuffer->GetCount(), 0, 0);
	}
}