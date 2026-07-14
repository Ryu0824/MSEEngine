#pragma once
#include <Renderer/Texture.h>
#include <d3d11.h>
#include <wrl/client.h>
#include <string>

namespace MSE
{
	class DirectX11Texture2D : public Texture2D
	{
	public:
		DirectX11Texture2D(const std::string& path);
		virtual ~DirectX11Texture2D() = default;

		virtual uint32_t GetWidth() const override { return m_Width; }
		virtual uint32_t GetHeight() const override { return m_Height; }
		virtual void Bind(uint32_t slot = 0) const override;

	private:
		uint32_t m_Width, m_Height = 0;
		std::string m_Path;

		Microsoft::WRL::ComPtr<ID3D11Texture2D> m_Texture;
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_SRV;
		Microsoft::WRL::ComPtr<ID3D11SamplerState> m_Sampler;
	};
}