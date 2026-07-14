#pragma once
#include <Scene/Component.h>
#include <DirectXMath.h>

namespace MSE
{
	class CameraComponent : public Component
	{
	public:
		DirectX::XMMATRIX projection;
		bool Primary = true;

		CameraComponent()
		{
			projection = DirectX::XMMatrixPerspectiveFovLH(DirectX::XMConvertToRadians(45.0f), 16.0f / 9.0f, 0.1f, 1000.0f);
		}

		virtual ~CameraComponent() = default;

		DirectX::XMMATRIX GetProjectionMatrix()
		{
			return projection;
		}
	};
}