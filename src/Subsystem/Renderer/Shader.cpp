#include "pch.h"
#include "Shader.h"
#include "RendererAPI.h"
#include <Platform/DirectX11/DirectX11Shader.h>

namespace MSE
{
	Ref<Shader> Shader::Create(const std::string& filepath)
	{
		switch (RendererAPI::GetAPI())
		{
		case RendererAPI::API::None:return nullptr;
		case RendererAPI::API::DirectX11:return CreateRef<DirectX11Shader>(filepath);
		}
		return nullptr;
	}
}