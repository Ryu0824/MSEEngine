#include "pch.h"
#include "RenderCommand.h"
#include <Platform/DirectX11/DirectX11RendererAPI.h>

namespace MSE
{
	Scope<RendererAPI> RenderCommand::s_RendererAPI = CreateScope<DirectX11RendererAPI>();
}