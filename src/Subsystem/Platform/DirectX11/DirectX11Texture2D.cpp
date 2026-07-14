#include "pch.h"
#include "DirectX11Texture2D.h"
#include <Vendor/stb_image/stb_image.h>
#include <iostream>

namespace MSE
{
	extern Microsoft::WRL::ComPtr<ID3D11Device> g_Device;
	extern Microsoft::WRL::ComPtr<ID3D11DeviceContext> g_DeviceContext;

	DirectX11Texture2D::DirectX11Texture2D(const std::string& path)
		:m_Path(path)
	{
		int width, height, channels;
		stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 4);

		if (!data)
		{
			std::cout << "[Texture Error] Failed to load image: " << path << std::endl;
			return;
		}

		m_Width = width;
		m_Height = height;

		D3D11_TEXTURE2D_DESC desc = {};
		desc.Width = m_Width;
		desc.Height = m_Height;
		desc.MipLevels = 1;
		desc.ArraySize = 1;
		desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		desc.SampleDesc.Count = 1;
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;

		D3D11_SUBRESOURCE_DATA sd = {};
		sd.pSysMem = data;
		sd.SysMemPitch = m_Width * 4;

		g_Device->CreateTexture2D(&desc, &sd, &m_Texture);
		g_Device->CreateShaderResourceView(m_Texture.Get(), nullptr, &m_SRV);

		D3D11_SAMPLER_DESC sampDesc = {};
		sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;

		g_Device->CreateSamplerState(&sampDesc, &m_Sampler);
		stbi_image_free(data);
	}

	void DirectX11Texture2D::Bind(uint32_t slot) const
	{
		g_DeviceContext->PSSetShaderResources(slot, 1, m_SRV.GetAddressOf());
		g_DeviceContext->PSSetSamplers(slot, 1, m_Sampler.GetAddressOf());
	}
}