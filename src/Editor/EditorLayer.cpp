#include "pch.h"
#include "EditorLayer.h"

void EditorLayer::OnAttach()
{
	m_ActiveScene = std::make_shared<MSE::Scene>();

	std::shared_ptr<MSE::VertexArray> vertexArray = MSE::VertexArray::Create();

	float vertices[] = {
		-0.5f,0.5f,0.0f, 1.0f,0.0f,0.0f,1.0f,

		0.5f, 0.5f,0.0f, 0.0,1.0f,0.0f,1.0f,

		0.5f,-0.5f,0.0f, 0.0f,0.0f,1.0f,1.0f,

		-0.5f,-0.5f,0.0f, 0.0f,1.0f,1.0f,1.0f
	};
	
	std::shared_ptr<MSE::VertexBuffer> vertexBuffer = MSE::VertexBuffer::Create(vertices, sizeof(vertices));

	MSE::BufferLayout layout = {
		{MSE::ShaderDataType::Float3,"POSITION"},
		{MSE::ShaderDataType::Float4,"COLOR"}
	};
	vertexBuffer->SetLayout(layout);
	vertexArray->AddVertexBuffer(vertexBuffer);

	uint32_t indices[] = { 0,1,2,0,2,3 };
	std::shared_ptr<MSE::IndexBuffer> indexBuffer = MSE::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));
	vertexArray->SetIndexBuffer(indexBuffer);

	std::shared_ptr<MSE::Shader> shader = MSE::Shader::Create(L"Assets/Shaders/Basic.hlsl");

	auto player = m_ActiveScene->CreateActor("Player");

	player->AddComponents<MSE::MeshComponent>(vertexArray, shader);
}

void EditorLayer::OnDetach()
{
	std::cout << "[EditorLayer] Detached!" << std::endl;
}

void EditorLayer::OnUpdate(MSE::Timestep ts)
{
	float clearColor[4] = { 0.2f,0.2f,0.2f,1.0f };
	MSE::RenderCommand::SetClearColor(clearColor);
	MSE::RenderCommand::Clear();

	MSE::Renderer::BeginScene();

	m_ActiveScene->OnUpdate(ts);

	MSE::Renderer::EndScene();
}

void EditorLayer::OnEvent(MSE::Event& event)
{
	if (event.GetEventType() != MSE::EventType::MouseMoved)
	{
		std::cout << "[Editor Event] " << event.ToString() << std::endl;
	}
}