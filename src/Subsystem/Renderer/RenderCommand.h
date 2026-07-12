#pragma once
#include "RendererAPI.h"
#include <memory>

namespace MSE
{
	class RenderCommand
	{
	public:
		inline static void SetClearColor(const float color[4])
		{
			s_RendererAPI->SetClearColor(color);
		}

		inline static void Clear()
		{
			s_RendererAPI->Clear();
		}

		inline static void DrawIndexed(const std::shared_ptr<IndexBuffer>& indexBuffer)
		{
			s_RendererAPI->DrawIndexed(indexBuffer);
		}

	private:
		static std::unique_ptr<RendererAPI> s_RendererAPI;
	};

}