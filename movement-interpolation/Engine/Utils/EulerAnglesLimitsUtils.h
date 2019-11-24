#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

class EulerAnglesLimitsUtils
{
	static float minAngle;
	static float maxAngle;
public:
	static bool IsCorrect(const glm::vec3& a)
	{
		if (a.x < minAngle || a.y < minAngle || a.z < minAngle ||
			a.x > maxAngle || a.y > maxAngle || a.z > maxAngle)
			return false;

		return true;
	}

	static glm::vec3 GetCerrected(const glm::vec3& a)
	{
		glm::vec3 out = a;

		while (out.x > 360)	out.x -= 360;
		while (out.x < 0)	out.x += 360;

		while (out.y > 360)	out.y -= 360;
		while (out.y < 0)	out.y += 360;

		while (out.z > 360)	out.z -= 360;
		while (out.z < 0)	out.z += 360;

		return out;
	}
};
