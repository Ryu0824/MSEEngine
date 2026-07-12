#include "pch.h"
#include "VertexArray.h"
#include "RendererAPI.h"
#include <Platform/DirectX11/DirectX11VertexArray.h>

namespace MSE
{
	std::shared_ptr<VertexArray> VertexArray::Create()
	{
		switch (RendererAPI::GetAPI())
		{
		case RendererAPI::API::None: return nullptr;
		case RendererAPI::API::DirectX11: return std::make_shared<DirectX11VertexArray>();
		}

		return nullptr;
	}
}