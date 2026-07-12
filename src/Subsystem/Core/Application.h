#pragma once
#include "LayerStack.h"
#include "Window.h"
#include <Event/ApplicationEvent.h>

namespace MSE
{
	class Application
	{
	public:
		Application();
		virtual ~Application();

		NOCOPYCLASS(Application)

		void Run();
		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		inline static Application& GetInstance() { return *m_Instance;}
		inline Window& GetWindow() { return *m_Window; }

	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);

	private:
		std::unique_ptr<Window> m_Window;
		bool m_bRunning = true;
		bool m_Minimized = false;
		LayerStack m_LayerStack;
		static Application* m_Instance;
	};

	Application* CreateApplication();
}