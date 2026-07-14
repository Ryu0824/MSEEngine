#pragma once

// Nocopy class Macro
#define NOCOPYCLASS(Typename) \
	Typename(const Typename&) = delete; \
	Typename& operator=(const Typename&) = delete;

// Bit Shift Macro
#define BIT(x) (1<<(x))

// Debugging Macro
#ifdef _DEBUG
#define ENGINE_ASSERT(x, ...) {if(!(x)){__debugbreak();}}
#else
#define ENGINE_ASSERT(x, ...)
#endif

#define MSE_BIND_EVENT_FN(fn) std::bind(&Application::fn, this, std::placeholders::_1)

namespace MSE
{
	// Unique_ptr
	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T,typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	// Shared_ptr

	template<typename T>
	using Ref = std::shared_ptr<T>;

	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}
}