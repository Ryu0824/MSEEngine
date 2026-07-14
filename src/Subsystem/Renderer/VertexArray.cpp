#include "pch.h"
#include "VertexArray.h"
#include "RendererAPI.h"
#include <Platform/DirectX11/DirectX11VertexArray.h>

namespace MSE
{
	Ref<VertexArray> VertexArray::Create()
	{
		switch (RendererAPI::GetAPI())
		{
		case RendererAPI::API::None: return nullptr;
		case RendererAPI::API::DirectX11: return CreateRef<DirectX11VertexArray>();
		}

		return nullptr;
	}
}