#pragma once
#include <Core/Timestep.h>

namespace MSE
{
	class Actor;

	class Component
	{
	public:
		virtual ~Component() = default;

		virtual void OnCreate() {};
		virtual void OnUpdate(Timestep ts){}
		virtual void OnDestroy(){}

	protected:
		Actor* m_Owner = nullptr;
		friend class Actor;
	};
}