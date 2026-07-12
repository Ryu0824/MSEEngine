#include "pch.h"
#include "DirectX11VertexArray.h"

namespace MSE
{
	DirectX11VertexArray::DirectX11VertexArray()
	{
	}

	void DirectX11VertexArray::Bind() const
	{
		for(const auto& vertexBuffer : m_VertexBuffers)
		{
			vertexBuffer->Bind();
		}

		if (m_IndexBuffer)
		{
			m_IndexBuffer->Bind();
		}
	}

	void DirectX11VertexArray::Unbind() const
	{
	}

	void DirectX11VertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
	{
		if (vertexBuffer->GetLayout().GetElements().empty())
		{
			return;
		}
		m_VertexBuffers.push_back(vertexBuffer);
	}

	void DirectX11VertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
	{
		m_IndexBuffer = indexBuffer;
	}
}