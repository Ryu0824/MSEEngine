#include "pch.h"
#include "EditorLayer.h"
#include <Scene/Components.h>
#include <DirectXMath.h>

void EditorLayer::OnAttach()
{
	m_ActiveScene = MSE::CreateRef<MSE::Scene>();

	MSE::Ref<MSE::VertexArray> vertexArray = MSE::VertexArray::Create();

	float vertices[] = {
		-0.5f,0.5f,0.0f, 1.0f,0.0f,0.0f,1.0f, 0.0f,0.0f,

		0.5f, 0.5f,0.0f, 0.0,1.0f,0.0f,1.0f, 1.0f,0.0f,

		0.5f,-0.5f,0.0f, 0.0f,0.0f,1.0f,1.0f, 1.0f,1.0f,

		-0.5f,-0.5f,0.0f, 0.0f,1.0f,1.0f,1.0f, 0.0f,1.0f
	};

	MSE::Ref<MSE::VertexBuffer> vertexBuffer = MSE::VertexBuffer::Create(vertices, sizeof(vertices));

	MSE::BufferLayout layout = {
		{MSE::ShaderDataType::Float3,"POSITION"},
		{MSE::ShaderDataType::Float4,"COLOR"},
		{MSE::ShaderDataType::Float2, "TEXCOORD"}
	};
	vertexBuffer->SetLayout(layout);
	vertexArray->AddVertexBuffer(vertexBuffer);

	uint32_t indices[] = { 0,1,2,0,2,3 };
	MSE::Ref<MSE::IndexBuffer> indexBuffer = MSE::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));
	vertexArray->SetIndexBuffer(indexBuffer);

	MSE::Ref<MSE::Shader> shader = MSE::Shader::Create(L"Assets/Shaders/Basic.hlsl");

	m_Texture = MSE::Texture2D::Create("Assets/Textures/TestImage.png");
	if (m_Texture) m_Texture->Bind(0);

	m_CameraCB = MSE::ConstantBuffer::Create(sizeof(DirectX::XMMATRIX));
	m_TransformCB = MSE::ConstantBuffer::Create(sizeof(DirectX::XMMATRIX));

	m_Player = m_ActiveScene->CreateActor("Player");
	m_Player->AddComponent<MSE::MeshComponent>(vertexArray, shader);
	m_Player->AddComponent<MSE::TransformComponent>();

	m_Camera = m_ActiveScene->CreateActor("Camera");
	auto camTransform = m_Camera->AddComponent<MSE::TransformComponent>();
	m_Camera->AddComponent<MSE::CameraComponent>();
	
	camTransform->Translation.z = -5.0f;	
}

void EditorLayer::OnDetach()
{
	std::cout << "[EditorLayer] Detached!" << std::endl;
}

void EditorLayer::OnUpdate(MSE::Timestep ts)
{
	auto transform = m_Camera->GetComponent<MSE::TransformComponent>();
	auto camera = m_Camera->GetComponent<MSE::CameraComponent>();

	auto playerTransform = m_Player->GetComponent<MSE::TransformComponent>();

	float moveSpeed = 2.0f;
	float rotSpeed = 3.0f;

	if (MSE::Input::IsKeyPressed('A')) transform->Translation.x -= moveSpeed * ts;
	if (MSE::Input::IsKeyPressed('D')) transform->Translation.x += moveSpeed * ts;
	if (MSE::Input::IsKeyPressed('W')) transform->Translation.y += moveSpeed * ts;
	if (MSE::Input::IsKeyPressed('S')) transform->Translation.y -= moveSpeed * ts;
	if (MSE::Input::IsKeyPressed('Z')) transform->Translation.z -= moveSpeed * ts;
	if (MSE::Input::IsKeyPressed('X')) transform->Translation.z += moveSpeed * ts;

	if (MSE::Input::IsKeyPressed('Q')) transform->Rotation.z += rotSpeed * ts;
	if (MSE::Input::IsKeyPressed('E')) transform->Rotation.z -= rotSpeed * ts;

	DirectX::XMMATRIX CamViewMatrix = transform->GetCameraViewMatrix();
	DirectX::XMMATRIX CamProjectionViewMatrix = camera->GetProjectionMatrix();

	DirectX::XMMATRIX camtransposed = DirectX::XMMatrixTranspose(CamViewMatrix * CamProjectionViewMatrix);
	DirectX::XMMATRIX playerTransposed = DirectX::XMMatrixTranspose(playerTransform->GetTransform());

	m_CameraCB->SetData(&camtransposed, sizeof(DirectX::XMMATRIX));
	m_CameraCB->Bind(0);

	m_TransformCB->SetData(&playerTransposed, sizeof(DirectX::XMMATRIX));
	m_TransformCB->Bind(1);

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