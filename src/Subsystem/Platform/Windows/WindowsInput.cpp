#include <pch.h>
#include <Core/Input.h>
#include <Core/Application.h>

namespace MSE
{
	bool Input::IsKeyPressed(int keycode)
	{
		return (GetAsyncKeyState(keycode) & 0x8000) != 0;
	}

	bool Input::IsMouseButtonPressed(int button)
	{
		int vkey = 0;

		switch (button)
		{
		case 0:vkey = VK_LBUTTON; break;
		case 1:vkey = VK_RBUTTON; break;
		case 2:vkey = VK_MBUTTON; break;
		}

		return (GetAsyncKeyState(vkey) & 0x8000) != 0;
	}

	std::pair<float, float> Input::GetMousePosition()
	{
		POINT pos;
		GetCursorPos(&pos);

		HWND hWnd = static_cast<HWND>(Application::GetInstance().GetWindow().GetNativeWindow().WindowHandle);
		ScreenToClient(hWnd, &pos);

		return { static_cast<float>(pos.x),static_cast<float>(pos.y) };
	}
	float Input::GetMouseX()
	{
		return GetMousePosition().first;
	}
	float Input::GetMouseY()
	{
		return GetMousePosition().second;
	}
}