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
	std::shared_ptr<MSE::Scene> m_ActiveScene;
};