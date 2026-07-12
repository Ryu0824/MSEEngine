#pragma once
#include <iostream>
#include <string>

namespace MSE {
    class Log
    {
    public:
        static void Init() {}

        template<typename... Args>
        static void PrintCore(const char* level, Args... args)
        {
            std::cout << "[MSE Core] " << level << ": ";
            (std::cout << ... << args);
            std::cout << std::endl;
        }

        template<typename... Args>
        static void PrintClient(const char* level, Args... args)
        {
            std::cout << "[App] " << level << ": ";
            (std::cout << ... << args);
            std::cout << std::endl;
        }
    };
}

#define MSE_CORE_TRACE(...) ::MSE::Log::PrintCore("TRACE", __VA_ARGS__)
#define MSE_CORE_INFO(...)  ::MSE::Log::PrintCore("INFO",  __VA_ARGS__)
#define MSE_CORE_WARN(...)  ::MSE::Log::PrintCore("WARN",  __VA_ARGS__)
#define MSE_CORE_ERROR(...) ::MSE::Log::PrintCore("ERROR", __VA_ARGS__)

#define MSE_TRACE(...)      ::MSE::Log::PrintClient("TRACE", __VA_ARGS__)
#define MSE_INFO(...)       ::MSE::Log::PrintClient("INFO",  __VA_ARGS__)
#define MSE_WARN(...)       ::MSE::Log::PrintClient("WARN",  __VA_ARGS__)
#define MSE_ERROR(...)      ::MSE::Log::PrintClient("ERROR", __VA_ARGS__)