#include "pch.h"
#include "Application.h"
#include <chrono>

namespace MSE
{
	Application* Application::m_Instance = nullptr;

	Application::Application()
	{
		m_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());

		m_Window->SetEventCallback([this](Event& e) {this->OnEvent(e); });
	}

	Application::~Application()
	{
		m_Instance = nullptr;
	}

	void Application::OnEvent(Event& e)
	{
		if (!e.IsInCategory(EventCategory::EventCategoryMouse))
		{
			// Test
			std::cout << "[Event] " << e << std::endl;
		}

		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(MSE_BIND_EVENT_FN(OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(MSE_BIND_EVENT_FN(OnWindowResize));

		for (auto iter = m_LayerStack.end(); iter != m_LayerStack.begin();)
		{
			(*--iter)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_bRunning = false;
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		if (e.GetWidth() == 0 || e.GetHeight() == 0)
		{
			m_Minimized = true;
			return false;
		}

		m_Minimized = false;

		//Renderer::OnWindowResize(e.GetWidth(),e.GetHeight());

		return false;
	}

	void Application::Run()
	{
		auto lastTime = std::chrono::high_resolution_clock::now();

		while (m_bRunning)
		{
			auto currentTime = std::chrono::high_resolution_clock::now();
			float time = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - lastTime).count();
			lastTime = currentTime;
			
			Timestep timestep = time;

			if (!m_Minimized)
			{
				for (Layer* layer : m_LayerStack)
					layer->OnUpdate(timestep);

				for (Layer* layer : m_LayerStack)
					layer->OnImGuiRender();
			}

			m_Window->OnUpdate();
		}
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* overlay)
	{
		m_LayerStack.PushOverlay(overlay);
	}
}