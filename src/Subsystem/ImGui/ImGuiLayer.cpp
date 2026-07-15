#include "pch.h"
#include "ImGuiLayer.h"
#include <Vendor/imgui/imgui.h>
#include <Vendor/imgui/imgui_impl_win32.h>
#include <Vendor/imgui/imgui_impl_dx11.h>
#include <d3d11.h>
#include <wrl/client.h>

namespace MSE
{
	extern Microsoft::WRL::ComPtr<ID3D11Device> g_Device;
	extern Microsoft::WRL::ComPtr<ID3D11DeviceContext> g_DeviceContext;
	extern HWND g_WindowHandle;

	extern Microsoft::WRL::ComPtr<ID3D11RenderTargetView> g_RenderTargetView;
	extern Microsoft::WRL::ComPtr<ID3D11DepthStencilView> g_DepthStencilView;

	ImGuiLayer::ImGuiLayer() : Layer("ImGuiLayer"){}

	void ImGuiLayer::OnAttach()
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;

		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

		ImGui::StyleColorsDark();

		ImGui_ImplWin32_Init(g_WindowHandle);
		ImGui_ImplDX11_Init(g_Device.Get(), g_DeviceContext.Get());
	}

	void ImGuiLayer::OnDetach()
	{
		ImGui_ImplDX11_Shutdown();
		ImGui_ImplWin32_Shutdown();
		ImGui::DestroyContext();
	}

	void ImGuiLayer::Begin()
	{
		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();
	}

	void ImGuiLayer::End()
	{
		ImGuiIO& io = ImGui::GetIO();
		io.DisplaySize = ImVec2(1280.f, 720.0f);

		ImGui::Render();
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();

			if (g_DeviceContext && g_RenderTargetView && g_DepthStencilView)
			{
				g_DeviceContext->OMSetRenderTargets(1, g_RenderTargetView.GetAddressOf(), g_DepthStencilView.Get());
			}
		}
	}
}