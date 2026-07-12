#include "pch.h"
#include "Shader.h"
#include "RendererAPI.h"
#include <Platform/DirectX11/DirectX11Shader.h>

namespace MSE
{
	std::shared_ptr<Shader> Shader::Create(const std::wstring& filepath)
	{
		switch (RendererAPI::GetAPI())
		{
		case RendererAPI::API::None:return nullptr;
		case RendererAPI::API::DirectX11:return std::make_shared<DirectX11Shader>(filepath);
		}
		return nullptr;
	}
}