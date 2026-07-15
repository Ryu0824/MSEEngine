#pragma once
#ifdef _WIN32
	#include <Windows.h>
#endif

namespace MSE
{
	struct NativeWindowInfo
	{
#ifdef _WIN32
		HWND WindowHandle = nullptr;
#endif
	};
}