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

		std::shared_ptr<Actor> CreateActor(const std::string& name = "Actor")
		{
			auto actor = std::make_shared<Actor>(name);
			actor->m_Scene = this;
			m_Actors.push_back(actor);
			return actor;
		}

	private:
		std::vector<std::shared_ptr<Actor>> m_Actors;
	};
}