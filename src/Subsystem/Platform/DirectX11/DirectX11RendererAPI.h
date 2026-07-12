#pragma once
#include <Renderer/RendererAPI.h>


namespace MSE
{
	class DirectX11RendererAPI : public RendererAPI
	{
	public:
		virtual void SetClearColor(const float color[4])override;
		virtual void Clear() override;
		virtual void DrawIndexed(const std::shared_ptr<IndexBuffer>& indexbuffer)override;

	private:
		float m_ClearColor[4] = { 0.1f,0.1f,0.1f,1.0f };
	};
}
