#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

template <typename T>
struct Configuration
{
	glm::vec3 position;
	T rotation;

	Configuration() : position(glm::vec3(0)) {  }
	Configuration(glm::vec3 _p) : position(_p) {  }
	Configuration(glm::vec3 _p, T _r) : position(_p), rotation(_r) { }

	Configuration(const Configuration<T>& _c) : position(_c.position), rotation(_c.rotation) { }
	Configuration<T>& operator=(const Configuration<T>& _c)
	{
		position = _c.position;
		rotation = _c.rotation;

		return *this;
	}
};
