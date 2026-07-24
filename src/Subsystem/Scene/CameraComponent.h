#pragma once
#include <Scene/Component.h>
#include <DirectXMath.h>

namespace MSE
{
	class CameraComponent : public Component
	{
	public:
		Matrix4 Projection;
		bool Primary = true;
		float AspectRatio = 16.0f / 9.0f;

		CameraComponent()
		{
			UpdateProjection();
		}

		virtual ~CameraComponent() = default;

		Matrix4 GetProjectionMatrix()
		{
			return Projection;
		}

		void SetViewportSize(uint32_t width, uint32_t height)
		{
			if (width > 0 && height > 0)
			{
				AspectRatio = (float)width / (float)height;
				UpdateProjection();
			}
		}

	private:
		void UpdateProjection()
		{
			Projection = Math::Perspective(Math::Radians(45.0f), AspectRatio, 0.1f, 1000.0f);
		}
	};
}