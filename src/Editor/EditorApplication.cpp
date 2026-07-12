#include "pch.h"
#include "EditorApplication.h"
#include "EditorLayer.h"

EditorApplication::EditorApplication()
{
    PushLayer(new EditorLayer());
}

EditorApplication::~EditorApplication()
{
}

MSE::Application* MSE::CreateApplication()
{
    return new EditorApplication();
}

#include <EntryPoint.h>