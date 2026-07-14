#pragma once
#include "Component.h"
#include <string>
#include <vector>
#include <memory>
#include <typeindex>
#include <unordered_map>

namespace MSE
{
	class Scene;

	class Actor
	{
	public:
		Actor(const std::string& name = "Actor") :m_Name(name) {};
		virtual ~Actor() = default;

		void OnUpdate(Timestep ts)
		{
			for (auto& comp : m_Components)
				comp->OnUpdate(ts);
		}

		const std::string& GetName() const { return m_Name; }

		template<typename T, typename... Args>
		Ref<T> AddComponents(Args&&... args)
		{
			auto component = CreateRef<T>(std::forward<Args>(args)...);

			component->m_Owner = this;

			m_Components.push_back(component);

			m_ComponentMap[typeid(T)] = component;
			component->OnCreate();
			return component;
		}

		template<typename T>
		Ref<T> GetComponent()
		{
			auto it = m_ComponentMap.find(typeid(T));
			if (it != m_ComponentMap.end())
				return std::static_pointer_cast<T>(it->second);
			return nullptr;
		}

	private:
		std::string m_Name;
		Scene* m_Scene = nullptr;

		std::vector<Ref<Component>> m_Components;
		std::unordered_map<std::type_index, Ref<Component>> m_ComponentMap;

		friend class Scene;
	};
}