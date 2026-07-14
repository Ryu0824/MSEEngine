#pragma once
#include <string>
#include <Renderer/Buffer.h>

namespace MSE
{
	class Shader
	{
	public:
		virtual ~Shader() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void BindLayout(const BufferLayout& layout) = 0;

		static Ref<Shader> Create(const std::wstring& filepath);
	};
}