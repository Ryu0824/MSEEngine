#pragma once
#include <Renderer/GraphicsContext.h>
#include "DirectX11Shader.h"
#include "DirectX11Buffer.h"
#include <d3d11.h>
#include <wrl/client.h>

namespace MSE
{
	class DirectX11Context : public GraphicsContext
	{
	public:
		DirectX11Context(HWND windowHandle);
		virtual ~DirectX11Context() = default;

		virtual void Init() override;
		virtual void SwapBuffers() override;

		virtual void Resize(uint32_t width, uint32_t height) override;

	private:
		HWND m_WindowHandle;

		Microsoft::WRL::ComPtr<ID3D11Device> m_Device;
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_DeviceContext;
		Microsoft::WRL::ComPtr<IDXGISwapChain> m_SwapChain;
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_RenderTargetView;

		Microsoft::WRL::ComPtr<ID3D11Texture2D> m_DepthStencilBuffer;
		Microsoft::WRL::ComPtr<ID3D11DepthStencilState> m_DepthStencilState;
		Microsoft::WRL::ComPtr<ID3D11DepthStencilView> m_DepthStencilView;
	};
}