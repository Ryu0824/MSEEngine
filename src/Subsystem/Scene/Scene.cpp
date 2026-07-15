#include "pch.h"
#include "Scene.h"

namespace MSE
{
	void Scene::OnViewportResize(uint32_t width, uint32_t height)
	{
		for (auto& actor : m_Actors)
		{
			if (actor->HasComponent<CameraComponent>())
			{
				auto camera = actor->GetComponent<CameraComponent>();
				camera->SetViewportSize(width, height);
			}
		}
	}
}