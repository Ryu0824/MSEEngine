#include "pch.h"
#include "Renderer.h"
#include "Shader.h"
#include "VertexArray.h"
#include "RenderCommand.h"

namespace MSE
{
	void Renderer::BeginScene()
	{

	}

	void Renderer::EndScene()
	{

	}

	void Renderer::Submit(const std::shared_ptr<Shader>& shader,
		const std::shared_ptr<VertexArray>& vertexArray)
	{
		shader->Bind();

		if (!vertexArray->GetVertexBuffers().empty())
		{
			shader->BindLayout(vertexArray->GetVertexBuffers()[0]->GetLayout());
		}

		vertexArray->Bind();

		RenderCommand::DrawIndexed(vertexArray->GetIndexBuffer());
	}
}