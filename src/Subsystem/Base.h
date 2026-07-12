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