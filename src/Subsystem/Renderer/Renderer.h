#pragma once
#include <DirectXMath.h>
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

		static void BeginScene(const DirectX::XMMATRIX& viewProjection);
		static void EndScene();

		static void Submit(const Ref<Shader>& shader,
			const Ref<VertexArray>&  vertexArray,
			const DirectX::XMMATRIX& transform);
	};
}