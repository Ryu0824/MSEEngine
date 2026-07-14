#pragma once
#include <Core/Window.h>
#include <Renderer/GraphicsContext.h>

namespace MSE
{
	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();

		void OnUpdate() override;

		unsigned int GetWidth() const override { return m_Data.Width; }
		unsigned int GetHeight() const override { return m_Data.Height; }

		void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }
		void SetVSync(bool enabled) override { m_Data.VSync = enabled; };
		bool IsVSync() const override { return m_Data.VSync; }

		inline virtual void* GetNativeWindow() override { return m_WindowHandle; }

	private:
		virtual void Init(const WindowProps& props);
		virtual void Shutdown();

		Scope<GraphicsContext> m_Context;

	private:
		struct WindowData
		{
			std::string Title;
			unsigned int Width, Height;
			bool VSync;

			EventCallbackFn EventCallback;
		};

		WindowData m_Data;
		void* m_WindowHandle;

		static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	};
}