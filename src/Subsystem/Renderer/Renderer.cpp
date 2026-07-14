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

	void Renderer::Submit(const Ref<Shader>& shader,
		const Ref<VertexArray>& vertexArray)
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