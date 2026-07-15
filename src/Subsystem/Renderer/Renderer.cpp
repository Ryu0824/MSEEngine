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
			s_Data->cameraCB = ConstantBuffer::Create(sizeof(DirectX::XMMATRIX));
			s_Data->TransformCB = ConstantBuffer::Create(sizeof(DirectX::XMMATRIX));
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

	void Renderer::BeginScene(const DirectX::XMMATRIX& viewProjection)
	{
		Init();

		DirectX::XMMATRIX transposedVP = DirectX::XMMatrixTranspose(viewProjection);
		s_Data->cameraCB->SetData(&transposedVP, sizeof(DirectX::XMMATRIX));
		s_Data->cameraCB->Bind(0);
	}

	void Renderer::EndScene()
	{
	}

	void Renderer::Submit(const Ref<Shader>& shader,
		const Ref<VertexArray>& vertexArray,
		const DirectX::XMMATRIX& transform)
	{
		DirectX::XMMATRIX transposedTransform = DirectX::XMMatrixTranspose(transform);
		s_Data->TransformCB->SetData(&transposedTransform, sizeof(DirectX::XMMATRIX));
		s_Data->TransformCB->Bind(1);

		shader->Bind();

		if (!vertexArray->GetVertexBuffers().empty())
		{
			shader->BindLayout(vertexArray->GetVertexBuffers()[0]->GetLayout());
		}

		vertexArray->Bind();

		RenderCommand::DrawIndexed(vertexArray->GetIndexBuffer());
	}
}