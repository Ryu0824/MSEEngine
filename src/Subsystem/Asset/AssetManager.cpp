#include "pch.h"
#include "AssetManager.h"

namespace MSE {

    std::unordered_map<std::string, Ref<Resource>> AssetManager::s_Resource;

    void AssetManager::Clear()
    {
        s_Resource.clear();
    }
}