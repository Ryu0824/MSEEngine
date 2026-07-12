#pragma once
#include <Renderer/Shader.h>
#include <d3d11.h>
#include <wrl/client.h>
#include <string>

namespace MSE
{
	class DirectX11Shader : public Shader
	{
	public:
		DirectX11Shader(const std::wstring& filepath);
		virtual ~DirectX11Shader() = default;

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void BindLayout(const BufferLayout& layout) override;

		ID3DBlob* GetVertexShaderBlob() const { return m_VSBlob.Get(); }

	private:
		Microsoft::WRL::ComPtr<ID3D11VertexShader> m_VertexShader;
		Microsoft::WRL::ComPtr<ID3D11PixelShader> m_PixelShader;
		Microsoft::WRL::ComPtr<ID3DBlob> m_VSBlob;

		Microsoft::WRL::ComPtr<ID3D11InputLayout> m_InputLayout;
	};
}