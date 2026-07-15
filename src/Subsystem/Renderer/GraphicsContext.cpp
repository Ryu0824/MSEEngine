#include "pch.h"
#include "GraphicsContext.h"
#include <Renderer/RendererAPI.h>
#include <Platform/DirectX11/DirectX11Context.h>

namespace MSE {

    std::unique_ptr<GraphicsContext> GraphicsContext::Create(const NativeWindowInfo& windowInfo)
    {
        switch (RendererAPI::GetAPI())
        {
        case RendererAPI::API::None:
            return nullptr;

        case RendererAPI::API::DirectX11:
            return CreateScope<DirectX11Context>(windowInfo.WindowHandle);
        }

        return nullptr;
    }
}