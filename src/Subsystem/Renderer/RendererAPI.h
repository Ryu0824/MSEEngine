#pragma once
#include "Buffer.h"
#include <memory>

namespace MSE
{
	class RendererAPI
	{
	public:
		enum class API
		{
			None = 0,DirectX11=1
		};

	public:
		virtual ~RendererAPI() = default;

		virtual void SetClearColor(const float color[4]) = 0;
		virtual void Clear() = 0;

		virtual void DrawIndexed(const std::shared_ptr<IndexBuffer>& indexbuffer) = 0;

		inline static API GetAPI() { return s_API; }

	private:
		static API s_API;
	};
}