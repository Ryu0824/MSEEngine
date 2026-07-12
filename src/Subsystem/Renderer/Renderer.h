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

		static void Submit(const std::shared_ptr<Shader>& shader,
			const std::shared_ptr<VertexArray>&  vertexArray);
	};
}