#include "pch.h"
#include "Buffer.h"
#include "RendererAPI.h"
#include <Platform/DirectX11/DirectX11Buffer.h>
#include <iostream>

namespace MSE
{
	std::shared_ptr<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (RendererAPI::GetAPI())
		{
		case RendererAPI::API::None:return nullptr;
		case RendererAPI::API::DirectX11: return std::make_shared<DirectX11VertexBuffer>(vertices, size);
		}
		return nullptr;
	}

	std::shared_ptr<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t count)
	{
		switch (RendererAPI::GetAPI())
		{
		case RendererAPI::API::None:return nullptr;
		case RendererAPI::API::DirectX11: return std::make_shared<DirectX11IndexBuffer>(indices, count);
		}
		return nullptr;
	}
}