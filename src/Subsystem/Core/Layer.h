#pragma once
#include <Core/Timestep.h>
#include <Event/Event.h>

namespace MSE
{
	class Layer
	{
	public:
		Layer(const std::string& debugname = "Layer", bool isOverlay = false)
			:m_DebugName(debugname), m_IsOverlay(isOverlay) {}
		virtual ~Layer() = default;

		virtual void OnAttach() {};
		virtual void OnDetach() {};
		virtual void OnUpdate(Timestep ts) {};
		virtual void OnImGuiRender() {};

		virtual void OnEvent(Event& event) {};

		inline const std::string& GetName() const { return m_DebugName; }
		inline bool IsOverlay() const { return m_IsOverlay; }

	private:
		std::string m_DebugName;
		bool m_IsOverlay;
	};
}
