#include "pch.h"
#include <Renderer/Texture.h>
#include <Renderer/RendererAPI.h>
#include <Platform/DirectX11/DirectX11Texture2D.h>

namespace MSE
{
	Ref<Texture2D> Texture2D::Create(const std::string& path)
	{
		switch (RendererAPI::GetAPI())
		{
		case RendererAPI::API::None: return nullptr;
		case RendererAPI::API::DirectX11: return CreateRef<DirectX11Texture2D>(path);
		}
	}
}