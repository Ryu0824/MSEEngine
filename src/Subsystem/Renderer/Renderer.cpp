#include "pch.h"
#include "Renderer.h"
#include "Shader.h"
#include "VertexArray.h"
#include "RenderCommand.h"

namespace MSE
{
	struct RenderData
	{
		Ref<ConstantBuffer> cameraCB;
		Ref<ConstantBuffer> TransformCB;
	};

	static RenderData* s_Data = nullptr;
		
	void Renderer::Init()
	{
		if (!s_Data)
		{
			s_Data = new RenderData();
			s_Data->cameraCB = ConstantBuffer::Create(sizeof(Matrix4));
			s_Data->TransformCB = ConstantBuffer::Create(sizeof(Matrix4));
		}
	}

	void Renderer::Shutdown()
	{
		if (s_Data)
		{
			delete s_Data;
			s_Data = nullptr;
		}
	}

	void Renderer::BeginScene(const Matrix4& viewProjection)
	{
		Init();

		s_Data->cameraCB->SetData(&viewProjection, sizeof(Matrix4));
		s_Data->cameraCB->Bind(0);
	}

	void Renderer::EndScene()
	{
	}

	void Renderer::Submit(const Ref<Shader>& shader,
		const Ref<VertexArray>& vertexArray,
		const Matrix4& transform)
	{
		s_Data->TransformCB->SetData(&transform, sizeof(Matrix4));
		s_Data->TransformCB->Bind(1);

		shader->Bind();

		if (!vertexArray->GetVertexBuffers().empty())
		{
			shader->BindLayout(vertexArray->GetVertexBuffers()[0]->GetLayout());
		}

		vertexArray->Bind();

		RenderCommand::DrawIndexed(vertexArray->GetIndexBuffer());
	}

	void Renderer::OnWindowResize(uint32_t width, uint32_t height)
	{
		
	}
}