#pragma once

#define GLM_FORCE_INTRINSICS
#define GLM_FORCE_LEFT_HANDED        
#define GLM_FORCE_DEPTH_ZERO_TO_ONE  
#include <Vendor/glm/glm.hpp>
#include <Vendor/glm/gtc/matrix_transform.hpp>
#include <Vendor/glm/gtc/type_ptr.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <Vendor/glm/gtx/quaternion.hpp>

namespace MSE {
	using Vector2 = glm::vec2;
	using Vector3 = glm::vec3;
	using Vector4 = glm::vec4;
	using Matrix3 = glm::mat3;
	using Matrix4 = glm::mat4;
	using Quaternion = glm::quat;

	namespace Math {
		inline Matrix4 Translate(const Matrix4& m, const Vector3& v) { return glm::translate(m, v); }
		inline Matrix4 Scale(const Matrix4& m, const Vector3& v) { return glm::scale(m, v); }
		inline float Radians(float degrees) { return glm::radians(degrees); }

		inline Matrix4 Transpose(const Matrix4& m) { return glm::transpose(m); }
		inline Matrix4 Inverse(const Matrix4& m) { return glm::inverse(m); }

		inline Matrix4 ToMat4(const Quaternion& q) { return glm::toMat4(q); }
		inline Quaternion Quat(const Vector3& eulerAngles) { return glm::quat(eulerAngles); }
		inline Matrix4 Perspective(float fovY, float aspect, float zNear, float zFar) { return glm::perspective(fovY, aspect, zNear, zFar); }
		inline float* ValuePtr(Vector3& v) { return glm::value_ptr(v); }
	}
}