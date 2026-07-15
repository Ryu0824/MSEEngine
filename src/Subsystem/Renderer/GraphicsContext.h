#pragma once

#include <memory>
#include <Core/NativeWindowInfo.h>
namespace MSE
{
	class GraphicsContext
	{
	public:
		virtual ~GraphicsContext() = default;

		virtual void Init() = 0;
		virtual void SwapBuffers() = 0;
		virtual void Resize(uint32_t width, uint32_t height) = 0;

		static Scope<GraphicsContext> Create(const NativeWindowInfo& windowInfo);
	};
}