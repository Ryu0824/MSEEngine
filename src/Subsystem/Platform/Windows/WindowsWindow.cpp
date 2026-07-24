#include "pch.h"
#include "WindowsWindow.h"
#include <Event/ApplicationEvent.h>
#include <Event/MouseEvent.h>
#include <Event/KeyEvent.h>
#include <Platform/DirectX11/DirectX11Context.h>

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

namespace MSE
{
	HWND g_WindowHandle = nullptr;

	LRESULT CALLBACK WindowsWindow::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		if (ImGui_ImplWin32_WndProcHandler(hwnd, msg, wParam, lParam))
			return true;

		WindowData* data = nullptr;

		if (msg == WM_NCCREATE)
		{
			CREATESTRUCT* pCreate = reinterpret_cast<CREATESTRUCT*>(lParam);
			data = static_cast<WindowData*>(pCreate->lpCreateParams);
			SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(data));
		}
		else
		{
			data = reinterpret_cast<WindowData*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
		}

		if (data)
		{
			switch (msg)
			{
			case WM_CLOSE:
			{
				WindowCloseEvent event;
				data->EventCallback(event); 
				return 0; 
			}
			case WM_SIZE:
			{
				data->Width = LOWORD(lParam);
				data->Height = HIWORD(lParam);
				WindowResizeEvent event(data->Width, data->Height);

				if (data->EventCallback)
					data->EventCallback(event);
				break;
			}
			case WM_KEYDOWN:
			case WM_SYSKEYDOWN:
			{
				int keycode = static_cast<int>(wParam);

				int repeatCount = (lParam & (1 << 30)) ? 1 : 0;

				KeyPressedEvent event(keycode, repeatCount);
				data->EventCallback(event);
				break;
			}

			case WM_KEYUP:
			case WM_SYSKEYUP:
			{
				int keycode = static_cast<int>(wParam);
				KeyReleasedEvent event(keycode);
				data->EventCallback(event);
				break;
			}

			case WM_CHAR:
			{
				int keycode = static_cast<int>(wParam);
				KeyTypedEvent event(keycode);
				data->EventCallback(event);
				break;
			}
			case WM_MOUSEMOVE:
			{
				float xPos = static_cast<float>(GET_X_LPARAM(lParam));
				float yPos = static_cast<float>(GET_Y_LPARAM(lParam));

				MouseMovedEvent event(xPos, yPos);
				data->EventCallback(event);
				break;
			}

			case WM_LBUTTONDOWN:
			case WM_RBUTTONDOWN:
			case WM_MBUTTONDOWN:
			{
				int button = 0;
				if (msg == WM_LBUTTONDOWN) button = 0;
				else if (msg == WM_RBUTTONDOWN) button = 1;
				else if (msg == WM_MBUTTONDOWN) button = 2;

				MouseButtonPressedEvent event(button);
				data->EventCallback(event);
				break;
			}

			case WM_LBUTTONUP:
			case WM_RBUTTONUP:
			case WM_MBUTTONUP:
			{
				int button = 0;
				if (msg == WM_LBUTTONUP) button = 0;
				else if (msg == WM_RBUTTONUP) button = 1;
				else if (msg == WM_MBUTTONUP) button = 2;

				MouseButtonReleasedEvent event(button);
				data->EventCallback(event);
				break;
			}

			case WM_MOUSEWHEEL:
			{
				float yOffset = static_cast<float>(GET_WHEEL_DELTA_WPARAM(wParam)) / static_cast<float>(WHEEL_DELTA);
				float xOffset = 0.0f;

				MouseScrolledEvent event(xOffset, yOffset);
				data->EventCallback(event);
				break;
			}
			}
		}

		return DefWindowProc(hwnd, msg, wParam, lParam);
	}

	WindowsWindow::WindowsWindow(const WindowProps& props)
		:m_Data{},
		m_WindowHandle(nullptr)
	{
		Init(props);
	}

	WindowsWindow::~WindowsWindow()
	{
		Shutdown();
	}

	Window* Window::Create(const WindowProps& props)
	{
		return new WindowsWindow(props);
	}

	void WindowsWindow::Init(const WindowProps& props)
	{
		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;

		WNDCLASSEX wc = { 0 };
		wc.cbSize = sizeof(WNDCLASSEX);
		wc.style = CS_HREDRAW | CS_VREDRAW;
		wc.lpfnWndProc = WindowsWindow::WndProc;
		wc.hInstance = GetModuleHandle(nullptr);
		wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
		wc.lpszClassName = L"MSE_Engine_Window";

		RegisterClassEx(&wc);

		// Temp
		std::wstring wTitle(m_Data.Title.begin(), m_Data.Title.end());

		HWND hwnd = CreateWindowEx(
			0,
			wc.lpszClassName,
			wTitle.c_str(),
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT, CW_USEDEFAULT, m_Data.Width, m_Data.Height,
			nullptr, nullptr, wc.hInstance,
			&m_Data
		);

		g_WindowHandle = hwnd;

		m_WindowHandle = hwnd;

		ShowWindow(hwnd, SW_SHOW);
	}

	void WindowsWindow::OnUpdate()
	{
		MSG msg;
		
		while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	void WindowsWindow::Shutdown()
	{
		DestroyWindow(static_cast<HWND>(m_WindowHandle));
	}

	NativeWindowInfo WindowsWindow::GetNativeWindow() const
	{
		NativeWindowInfo info;
		info.WindowHandle = static_cast<HWND>(m_WindowHandle);
		return info;
	}
}