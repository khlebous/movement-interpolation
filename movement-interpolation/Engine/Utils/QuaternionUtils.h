#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

class QuaternionUtils
{
public:
	static glm::quat EulerDegreeToQuaternion(glm::vec3 euler)
	{
		return EulerRadiansToQuaternion(glm::radians(euler));
	}

	static glm::quat EulerRadiansToQuaternion(glm::vec3 euler)
	{
		return glm::quat(glm::vec3(euler.y, euler.x, euler.z));
	}
};
