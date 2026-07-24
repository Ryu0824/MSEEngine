#pragma once
#include <Math/Math.h>
#include <memory>

namespace MSE
{
	class Shader;
	class VertexArray;

	class Renderer
	{
	public:
		static void Init();
		static void Shutdown();

		static void BeginScene(const Matrix4& viewProjection);
		static void EndScene();

		static void Submit(const Ref<Shader>& shader,
			const Ref<VertexArray>& vertexArray,
			const Matrix4& transform);

		static void OnWindowResize(uint32_t width, uint32_t height);
	};
}