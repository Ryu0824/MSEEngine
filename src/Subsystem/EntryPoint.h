#pragma once
#ifdef _WIN32
#include <Platform/Windows/WindowsWindow.h>
#include <Windows.h>

extern MSE::Application* MSE::CreateApplication();

int WINAPI WinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nShowCmd)
{
	auto app = MSE::CreateApplication();

	app->Run();

	delete app;

	return 0;
}
#endif