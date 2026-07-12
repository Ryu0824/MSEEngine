#include "pch.h"
#include "RenderCommand.h"
#include <Platform/DirectX11/DirectX11RendererAPI.h>

namespace MSE
{
	std::unique_ptr<RendererAPI> RenderCommand::s_RendererAPI = std::make_unique<DirectX11RendererAPI>();
}