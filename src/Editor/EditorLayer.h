#pragma once
class EditorLayer : public MSE::Layer
{
public:
	EditorLayer() : MSE::Layer("EditorLayer") {}
	virtual ~EditorLayer() = default;

	virtual void OnAttach()						override;
	virtual void OnDetach()						override;
	virtual void OnUpdate(MSE::Timestep ts)		override;
	virtual void OnImGuiRender() override {};
	virtual void OnEvent(MSE::Event& event)		override;

private:
	MSE::Ref<MSE::Scene> m_ActiveScene;

	MSE::Ref<MSE::Actor> m_Player;
	MSE::Ref<MSE::Actor> m_Camera;

	MSE::Ref<MSE::ConstantBuffer> m_CameraCB;
	MSE::Ref<MSE::ConstantBuffer> m_TransformCB;

	MSE::Ref<MSE::Texture2D> m_Texture;
};