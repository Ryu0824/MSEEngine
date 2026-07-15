#pragma once
#include <Scene/Component.h>
#include <DirectXMath.h>

namespace MSE
{
	class TransformComponent : public Component
	{
	public:
		DirectX::XMFLOAT3 Translation = { 0.0f,0.0f,0.0f };
		DirectX::XMFLOAT3 Rotation = { 0.0f,0.0f,0.0f };
		DirectX::XMFLOAT3 Scale = { 1.0f,1.0f,1.0f };

		TransformComponent() = default;
		TransformComponent(const TransformComponent&) = default;
		TransformComponent(const DirectX::XMFLOAT3& translation)
			:Translation(translation) {
		}

		DirectX::XMMATRIX GetTransform() const
		{
			return DirectX::XMMatrixScaling(Scale.x, Scale.y, Scale.z) *
				DirectX::XMMatrixRotationRollPitchYaw(DirectX::XMConvertToRadians(Rotation.x),
					DirectX::XMConvertToRadians(Rotation.y),
					DirectX::XMConvertToRadians(Rotation.z)) *
				DirectX::XMMatrixTranslation(Translation.x, Translation.y, Translation.z);
		}

		DirectX::XMMATRIX GetCameraViewMatrix() const
		{
			return DirectX::XMMatrixTranslation(-Translation.x, -Translation.y, -Translation.z) *
				DirectX::XMMatrixTranspose(DirectX::XMMatrixRotationRollPitchYaw(Rotation.x, Rotation.y, Rotation.z));
		}
	};
}