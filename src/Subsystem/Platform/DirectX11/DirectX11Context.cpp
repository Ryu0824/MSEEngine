#include "pch.h"
#include "DirectX11Context.h"
#include "DirectX11Shader.h"
#include <iostream>

#include<d3dcompiler.h>
#pragma comment(lib, "d3dcompiler.lib")

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")

namespace MSE
{
	Microsoft::WRL::ComPtr<ID3D11Device> g_Device;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> g_DeviceContext;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> g_RenderTargetView;

	DirectX11Context::DirectX11Context(HWND windowHandle)
		:m_WindowHandle(windowHandle)
	{
		if (!m_WindowHandle)
			std::cout << "[DX11 Error] 윈도우 핸들이 null입니다.!" << std::endl;
	}

	void DirectX11Context::Init()
	{
		DXGI_SWAP_CHAIN_DESC scd = {};
		scd.BufferCount = 1;
		scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		scd.OutputWindow = m_WindowHandle;
		scd.SampleDesc.Count = 1;
		scd.Windowed = TRUE;
		scd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

		UINT createDeviceFlags = 0;
#ifdef _DEBUG
		createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

		HRESULT hr = D3D11CreateDeviceAndSwapChain(
			nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, createDeviceFlags,
			nullptr, 0, D3D11_SDK_VERSION, &scd,
			&m_SwapChain, &m_Device, nullptr, &m_DeviceContext
		);

		if (FAILED(hr))
		{
			std::cout << "[DX11 Error] 디바이스 및 스왑체인 생성 실패!" << std::endl;
			return;
		}

		Microsoft::WRL::ComPtr<ID3D11Texture2D> backbuffer;
		m_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backbuffer);
		m_Device->CreateRenderTargetView(backbuffer.Get(), nullptr, &m_RenderTargetView);

		g_Device = m_Device;
		g_DeviceContext = m_DeviceContext;
		g_RenderTargetView = m_RenderTargetView;

		m_DeviceContext->OMSetRenderTargets(1, m_RenderTargetView.GetAddressOf(), nullptr);

		std::cout << "[DirectX 11] 그래픽스 컨텍스트 초기화 성공!" << std::endl;

		D3D11_VIEWPORT vp = { 0.0f, 0.0f, 1280.0f, 720.0f, 0.0f, 1.0f };
		m_DeviceContext->RSSetViewports(1, &vp);

		m_DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		std::cout << "[DirectX 11] 순수 그래픽스 컨텍스트 초기화 성공!" << std::endl;
	}

	void DirectX11Context::SwapBuffers()
	{
		m_SwapChain->Present(1, 0);
	}
}