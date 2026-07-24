#pragma once
#include <string>
#include <unordered_map>
#include <memory>
#include <Asset/Resource.h>

namespace MSE
{
	class AssetManager
	{
	public:
		template <typename T>
		static Ref<T> GetResource(const std::string& filepath)
		{
			if (s_Resource.find(filepath) != s_Resource.end())
			{
				return std::dynamic_pointer_cast<T>(s_Resource[filepath]);
			}

			Ref<T> resource = T::Create(filepath);
			if (resource)
			{
				s_Resource[filepath] = resource;
			}

			return resource;
		}

		static void Clear();

	private:
		static std::unordered_map<std::string, Ref<Resource>> s_Resource;
	};
}