#pragma once
#include "Actor.h"
#include "Components.h"
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

			Ref<CameraComponent> mainCamera = nullptr;
			DirectX::XMMATRIX cameraViewProj;

			for (auto& actor : m_Actors)
			{
				if (actor->HasComponent<CameraComponent>())
				{
					mainCamera = actor->GetComponent<CameraComponent>();
					auto transform = actor->GetComponent<TransformComponent>();

					DirectX::XMMATRIX view = transform->GetCameraViewMatrix();
					DirectX::XMMATRIX proj = mainCamera->GetProjectionMatrix();
					cameraViewProj = view * proj;
					break;
				}
			}

			if (mainCamera)
			{
				Renderer::BeginScene(cameraViewProj);

				for (auto& actor : m_Actors)
				{
					if (actor->HasComponent<MeshComponent>() && actor->HasComponent<TransformComponent>())
					{
						auto mesh = actor->GetComponent<MeshComponent>();
						auto transform = actor->GetComponent<TransformComponent>();
						Renderer::Submit(mesh->m_Shader, mesh->m_VertexArray, transform->GetTransform());
					}
				}

				Renderer::EndScene();
			}
		}

		Ref<Actor> CreateActor(const std::string& name = "Actor")
		{
			auto actor = CreateRef<Actor>(name);
			actor->m_Scene = this;
			m_Actors.push_back(actor);
			return actor;
		}

		void OnViewportResize(uint32_t width, uint32_t height);

	private:
		std::vector<Ref<Actor>> m_Actors;
	};
}