#include "pch.h"
#include "DirectX11Shader.h"
#include <iostream>
#include <d3dcompiler.h>
#include <Utils/StringUtils.h>

namespace MSE
{
	extern Microsoft::WRL::ComPtr<ID3D11Device> g_Device;
	extern Microsoft::WRL::ComPtr<ID3D11DeviceContext> g_DeviceContext;

	static DXGI_FORMAT ShaderDataTypeToDXGIFormat(ShaderDataType type)
	{
		switch (type)
		{
		case ShaderDataType::Float: return DXGI_FORMAT_R32_FLOAT;
		case ShaderDataType::Float2: return DXGI_FORMAT_R32G32_FLOAT;
		case ShaderDataType::Float3: return DXGI_FORMAT_R32G32B32_FLOAT;
		case ShaderDataType::Float4: return DXGI_FORMAT_R32G32B32A32_FLOAT;
		case ShaderDataType::Int: return DXGI_FORMAT_R32_SINT;
		case ShaderDataType::Int2: return DXGI_FORMAT_R32G32_SINT;
		case ShaderDataType::Int3: return DXGI_FORMAT_R32G32B32_SINT;
		case ShaderDataType::Int4: return DXGI_FORMAT_R32G32B32A32_SINT;
		}
		return DXGI_FORMAT_UNKNOWN;
	}

	DirectX11Shader::DirectX11Shader(const std::string& filepath)
	{
		Microsoft::WRL::ComPtr<ID3DBlob> psBlob, errorBlob;
		std::wstring wideFilepath = Utils::ToWideString(filepath);


		UINT compileFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#ifdef _DEBUG
		compileFlags |= D3DCOMPILE_DEBUG;
#endif

		HRESULT hr = D3DCompileFromFile(
			wideFilepath.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE,
			"VS_Main", "vs_5_0", compileFlags, 0, &m_VSBlob, &errorBlob
		);

		if (FAILED(hr))
		{
			if (errorBlob)
				std::cout << "[Shader Error] " << (char*)errorBlob->GetBufferPointer() << std::endl;
			else
				std::cout << "[Shader Error] Filepath is Wrong! " << filepath << std::endl;
			return;
		}
		g_Device->CreateVertexShader(m_VSBlob->GetBufferPointer(), m_VSBlob->GetBufferSize(), nullptr, &m_VertexShader);

		hr = D3DCompileFromFile(
			wideFilepath.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE,
			"PS_Main", "ps_5_0", compileFlags, 0, &psBlob, &errorBlob
		);

		if (FAILED(hr))
		{
			if (errorBlob)
				std::cout << "[Shader Error] " << (char*)errorBlob->GetBufferPointer() << std::endl;
			return;
		}
		g_Device->CreatePixelShader(psBlob->GetBufferPointer(), psBlob->GetBufferSize(), nullptr, &m_PixelShader);
	}

	void DirectX11Shader::Bind() const
	{
		g_DeviceContext->VSSetShader(m_VertexShader.Get(), nullptr, 0);
		g_DeviceContext->PSSetShader(m_PixelShader.Get(), nullptr, 0);
	}

	void DirectX11Shader::Unbind() const
	{
		g_DeviceContext->VSSetShader(nullptr, nullptr, 0);
		g_DeviceContext->PSSetShader(nullptr, nullptr, 0);
	}

	void DirectX11Shader::BindLayout(const BufferLayout& layout)
	{
		if (m_InputLayout)
		{
			g_DeviceContext->IASetInputLayout(m_InputLayout.Get());
			return;
		}

		std::vector<D3D11_INPUT_ELEMENT_DESC> ied;
		const auto& elements = layout.GetElements();

		for (const auto& element : elements)
		{
			D3D11_INPUT_ELEMENT_DESC desc = {};
			desc.SemanticName = element.Name.c_str();
			desc.SemanticIndex = 0;
			desc.Format = ShaderDataTypeToDXGIFormat(element.Type);
			desc.InputSlot = 0;
			desc.AlignedByteOffset = element.Offset;
			desc.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
			desc.InstanceDataStepRate = 0;

			ied.push_back(desc);
		}

		g_Device->CreateInputLayout(ied.data(), (UINT)ied.size(),
			m_VSBlob->GetBufferPointer(), m_VSBlob->GetBufferSize(),
			&m_InputLayout);

		g_DeviceContext->IASetInputLayout(m_InputLayout.Get());
	}
}
