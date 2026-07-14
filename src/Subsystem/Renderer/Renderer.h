#pragma once
#include <memory>

namespace MSE
{
	class Shader;
	class VertexArray;

	class Renderer
	{
	public:
		static void BeginScene();
		static void EndScene();

		static void Submit(const Ref<Shader>& shader,
			const Ref<VertexArray>&  vertexArray);
	};
}