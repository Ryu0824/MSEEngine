#pragma once
#include "Actor.h"
#include <Core/Timestep.h>
#include <vector>
#include <memory>

namespace MSE
{
	class Scene
	{
	public:
		Scene() = default;
		~Scene() = default;

		void OnUpdate(Timestep ts)
		{
			for (auto& actor : m_Actors)
			{
				actor->OnUpdate(ts);
			}
		}

		Ref<Actor> CreateActor(const std::string& name = "Actor")
		{
			auto actor = CreateRef<Actor>(name);
			actor->m_Scene = this;
			m_Actors.push_back(actor);
			return actor;
		}

	private:
		std::vector<Ref<Actor>> m_Actors;
	};
}