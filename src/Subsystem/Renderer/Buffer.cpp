#include "pch.h"
#include "Buffer.h"
#include "RendererAPI.h"
#include <Platform/DirectX11/DirectX11Buffer.h>
#include <iostream>

namespace MSE
{
	Ref<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (RendererAPI::GetAPI())
		{
		case RendererAPI::API::None:return nullptr;
		case RendererAPI::API::DirectX11: return CreateRef<DirectX11VertexBuffer>(vertices, size);
		}
		return nullptr;
	}

	Ref<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t count)
	{
		switch (RendererAPI::GetAPI())
		{
		case RendererAPI::API::None:return nullptr;
		case RendererAPI::API::DirectX11: return CreateRef<DirectX11IndexBuffer>(indices, count);
		}
		return nullptr;
	}

	Ref<ConstantBuffer> ConstantBuffer::Create(uint32_t size)
	{
		switch (RendererAPI::GetAPI())
		{
		case RendererAPI::API::None:return nullptr;
		case RendererAPI::API::DirectX11: return CreateRef<DirectX11ConstantBuffer>(size);
		}
		return nullptr;
	}
}