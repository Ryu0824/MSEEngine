#include "pch.h"
#include "EditorLayer.h"
#include <Scene/Components.h>
#include <DirectXMath.h>
#include <Vendor/imgui/imgui.h>

void EditorLayer::OnAttach()
{
	m_ActiveScene = MSE::CreateRef<MSE::Scene>();

	MSE::Ref<MSE::VertexArray> vertexArray = MSE::VertexArray::Create();

	float vertices[] = {
		-0.5f, -0.5f, -0.5f,   1.0f, 1.0f, 1.0f, 1.0f,   0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,   1.0f, 1.0f, 1.0f, 1.0f,   1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,   1.0f, 1.0f, 1.0f, 1.0f,   1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,   1.0f, 1.0f, 1.0f, 1.0f,   0.0f, 0.0f,

		// 뒷면 (Back)
		 0.5f, -0.5f,  0.5f,   1.0f, 1.0f, 1.0f, 1.0f,   0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,   1.0f, 1.0f, 1.0f, 1.0f,   1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,   1.0f, 1.0f, 1.0f, 1.0f,   1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,   1.0f, 1.0f, 1.0f, 1.0f,   0.0f, 0.0f,

		 // 왼쪽면 (Left)
		 -0.5f, -0.5f,  0.5f,   1.0f, 1.0f, 1.0f, 1.0f,   0.0f, 1.0f,
		 -0.5f, -0.5f, -0.5f,   1.0f, 1.0f, 1.0f, 1.0f,   1.0f, 1.0f,
		 -0.5f,  0.5f, -0.5f,   1.0f, 1.0f, 1.0f, 1.0f,   1.0f, 0.0f,
		 -0.5f,  0.5f,  0.5f,   1.0f, 1.0f, 1.0f, 1.0f,   0.0f, 0.0f,

		 // 오른쪽면 (Right)
		  0.5f, -0.5f, -0.5f,   1.0f, 1.0f, 1.0f, 1.0f,   0.0f, 1.0f,
		  0.5f, -0.5f,  0.5f,   1.0f, 1.0f, 1.0f, 1.0f,   1.0f, 1.0f,
		  0.5f,  0.5f,  0.5f,   1.0f, 1.0f, 1.0f, 1.0f,   1.0f, 0.0f,
		  0.5f,  0.5f, -0.5f,   1.0f, 1.0f, 1.0f, 1.0f,   0.0f, 0.0f,

		  // 윗면 (Top)
		  -0.5f,  0.5f, -0.5f,   1.0f, 1.0f, 1.0f, 1.0f,   0.0f, 1.0f,
		   0.5f,  0.5f, -0.5f,   1.0f, 1.0f, 1.0f, 1.0f,   1.0f, 1.0f,
		   0.5f,  0.5f,  0.5f,   1.0f, 1.0f, 1.0f, 1.0f,   1.0f, 0.0f,
		  -0.5f,  0.5f,  0.5f,   1.0f, 1.0f, 1.0f, 1.0f,   0.0f, 0.0f,

		  // 아랫면 (Bottom)
		  -0.5f, -0.5f,  0.5f,   1.0f, 1.0f, 1.0f, 1.0f,   0.0f, 1.0f,
		   0.5f, -0.5f,  0.5f,   1.0f, 1.0f, 1.0f, 1.0f,   1.0f, 1.0f,
		   0.5f, -0.5f, -0.5f,   1.0f, 1.0f, 1.0f, 1.0f,   1.0f, 0.0f,
		  -0.5f, -0.5f, -0.5f,   1.0f, 1.0f, 1.0f, 1.0f,   0.0f, 0.0f
	};

	MSE::Ref<MSE::VertexBuffer> vertexBuffer = MSE::VertexBuffer::Create(vertices, sizeof(vertices));

	MSE::BufferLayout layout = {
		{MSE::ShaderDataType::Float3,"POSITION"},
		{MSE::ShaderDataType::Float4,"COLOR"},
		{MSE::ShaderDataType::Float2, "TEXCOORD"}
	};
	vertexBuffer->SetLayout(layout);
	vertexArray->AddVertexBuffer(vertexBuffer);

	uint32_t indices[] = {
		 0,  3,  2,  2,  1,  0,
		 4,  7,  6,  6,  5,  4,
		 8, 11, 10, 10,  9,  8,
		12, 15, 14, 14, 13, 12,
		16, 19, 18, 18, 17, 16,
		20, 23, 22, 22, 21, 20
	};

	MSE::Ref<MSE::IndexBuffer> indexBuffer = MSE::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));
	vertexArray->SetIndexBuffer(indexBuffer);

	MSE::Ref<MSE::Shader> shader = MSE::Shader::Create(L"Assets/Shaders/Basic.hlsl");

	m_Texture = MSE::Texture2D::Create("Assets/Textures/TestImage.png");
	if (m_Texture) m_Texture->Bind(0);

	m_Camera = m_ActiveScene->CreateActor("Camera");
	auto camTransform = m_Camera->AddComponent<MSE::TransformComponent>();
	m_Camera->AddComponent<MSE::CameraComponent>();
	camTransform->Translation.z = -10.0f;

	m_Player = m_ActiveScene->CreateActor("Player");
	m_Player->AddComponent<MSE::MeshComponent>(vertexArray, shader);
	m_Player->AddComponent<MSE::TransformComponent>();

	/// Test Code ///
	/*for (int y = -5; y < 5; y++)
	{
		for (int x = -5; x < 5; x++)
		{
			auto cube = m_ActiveScene->CreateActor("Cube");
			cube->AddComponent<MSE::MeshComponent>(vertexArray, shader);

			auto transform = cube->AddComponent<MSE::TransformComponent>();
			transform->Translation.x = (float)x * 1.5f;
			transform->Translation.y = (float)y * 1.5f;
			transform->Scale = { 0.8f, 0.8f, 0.8f };


			transform->Rotation.x = (float)x * 0.3f;
			transform->Rotation.y = (float)y * 0.3f;
		}
	}*/
}

void EditorLayer::OnDetach()
{
	std::cout << "[EditorLayer] Detached!" << std::endl;
}

void EditorLayer::OnUpdate(MSE::Timestep ts)
{
	auto transform = m_Camera->GetComponent<MSE::TransformComponent>();
	auto camera = m_Camera->GetComponent<MSE::CameraComponent>();

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


	float clearColor[4] = { 0.2f,0.2f,0.2f,1.0f };
	MSE::RenderCommand::SetClearColor(clearColor);
	MSE::RenderCommand::Clear();

	m_ActiveScene->OnUpdate(ts);
}

void EditorLayer::OnImGuiRender()
{
	ImGui::Begin("Inspector");

	if (m_Player)
	{
		ImGui::Text("Actor Name: Player");
		ImGui::Separator();

		auto transform = m_Player->GetComponent<MSE::TransformComponent>();

		if (transform)
		{
			ImGui::DragFloat3("Position", &transform->Translation.x, 0.05f);

			ImGui::DragFloat3("Rotation", &transform->Rotation.x, 1.0f);

			ImGui::DragFloat3("Scale", &transform->Scale.x, 0.02f, 0.1f, 10.0f);
		}
	}

	ImGui::End();
}

void EditorLayer::OnEvent(MSE::Event& event)
{
	if (event.GetEventType() != MSE::EventType::MouseMoved)
	{
		std::cout << "[Editor Event] " << event.ToString() << std::endl;
	}
}