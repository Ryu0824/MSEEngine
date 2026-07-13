#pragma once
#include <Scene/Component.h>
#include <Renderer/Shader.h>
#include <Renderer/VertexArray.h>
#include <Renderer/Renderer.h>
#include <memory>

namespace MSE
{
	class MeshComponent :public Component
	{
	public:
		std::shared_ptr<VertexArray> m_VertexArray;
		std::shared_ptr<Shader> m_Shader;

		MeshComponent() = default;
		MeshComponent(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<Shader>& shader)
			:m_VertexArray(vertexArray), m_Shader(shader) {}

		virtual void OnUpdate(Timestep ts)override
		{
			if (m_VertexArray && m_Shader)
			{
				Renderer::Submit(m_Shader, m_VertexArray);
			}
		}
	};
}