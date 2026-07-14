#pragma once
#include <Renderer/Buffer.h>
#include <d3d11.h>
#include <wrl/client.h>

namespace MSE
{
	class DirectX11VertexBuffer : public VertexBuffer
	{
	public:
		DirectX11VertexBuffer(float* vertices, uint32_t size);
		virtual ~DirectX11VertexBuffer() = default;

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual const BufferLayout& GetLayout() const override { return m_Layout; }
		virtual void SetLayout(const BufferLayout& layout) override { m_Layout = layout; }

	private:
		Microsoft::WRL::ComPtr<ID3D11Buffer> m_Buffer;
		BufferLayout m_Layout;
	};

	class DirectX11IndexBuffer :public IndexBuffer
	{
	public:
		DirectX11IndexBuffer(uint32_t* indices, uint32_t count);
		virtual ~DirectX11IndexBuffer() = default;

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual uint32_t GetCount() const override { return m_Count; }

	private:
		Microsoft::WRL::ComPtr<ID3D11Buffer> m_Buffer;
		uint32_t m_Count;
	};

	class DirectX11ConstantBuffer :public ConstantBuffer
	{
	public:
		DirectX11ConstantBuffer(uint32_t size);
		virtual ~DirectX11ConstantBuffer() = default;

		virtual void Bind(uint32_t slot = 0) const override;
		virtual void SetData(const void* data, uint32_t size) override;

	private:
		Microsoft::WRL::ComPtr<ID3D11Buffer> m_Buffer;
	};
}