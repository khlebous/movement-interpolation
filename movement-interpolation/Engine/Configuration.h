#pragma once
#include <glm/glm.hpp>

template <typename T>
struct Configuration
{
	glm::vec3 position;
	T rotation;

	Configuration() : position(glm::vec3(0)) { }
	Configuration(glm::vec3 _p) : position(_p) { }
	Configuration(glm::vec3 _p, T _r) : position(_p), rotation(_r) { }

	Configuration(const Configuration& _c) : position(_c.position), rotation(_c.rotation) { }
	Configuration& operator=(const Configuration& _c)
	{
		position = _c.position;
		rotation = _c.rotation;

		return *this;
	}
};
