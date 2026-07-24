#pragma once
#include <Scene/Component.h>
#include <Math/Math.h>

namespace MSE
{
	class TransformComponent : public Component
	{
	public:
		Vector3 Translation = { 0.0f,0.0f,0.0f };
		Vector3 Rotation = { 0.0f,0.0f,0.0f };
		Vector3 Scale = { 1.0f,1.0f,1.0f };

		TransformComponent() = default;
		TransformComponent(const TransformComponent&) = default;
		TransformComponent(const Vector3& translation)
			:Translation(translation) {
		}

		Matrix4 GetTransform() const
		{
			Matrix4 rotation = Math::ToMat4(Math::Quat(Vector3(Math::Radians(Rotation.x), Math::Radians(Rotation.y), Math::Radians(Rotation.z))));

			return Math::Translate(Matrix4(1.0f), Translation) * rotation * Math::Scale(Matrix4(1.0f), Scale);
		}

		Matrix4 GetCameraViewMatrix() const
		{
			return Math::Transpose(Math::ToMat4(Math::Quat(Vector3(Math::Radians(Rotation.x), Math::Radians(Rotation.y), Math::Radians(Rotation.z))))) * 
				Math::Translate(Matrix4(1.0f), Vector3(-Translation.x, -Translation.y, -Translation.z));
		}
	};
}