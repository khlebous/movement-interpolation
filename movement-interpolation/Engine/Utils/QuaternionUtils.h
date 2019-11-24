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

	static glm::quat Lerp(const glm::quat & q1, const glm::quat& q2, float t)
	{
		return q1 * (1 - t) + q2 * t;
	}

	static glm::quat Slerp(const glm::quat& q1, const glm::quat& q2, float t)
	{
		glm::quat q3 = q2;
		float cosTheta = glm::dot(q1, q2);

		if (cosTheta < 0.0f)
		{
			q3 = -q2;
			cosTheta = -cosTheta;
		}

		if (cosTheta > 1.0f - glm::epsilon<float>())
		{
			return glm::quat(
				glm::mix(q1.w, q3.w, t),
				glm::mix(q1.x, q3.x, t),
				glm::mix(q1.y, q3.y, t),
				glm::mix(q1.z, q3.z, t));
		}
		else
		{
			float angle = acos(cosTheta);
			return (glm::sin((1.0f - t) * angle) * q1 + glm::sin(t * angle) * q3) / glm::sin(angle);
		}
	}
};
