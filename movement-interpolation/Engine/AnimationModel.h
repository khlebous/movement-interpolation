#pragma once
#include <glm/glm.hpp>
#include <vector>
#include <memory>
#include "Configuration.h"

template <typename T>
class AnimationModel
{
public:
	Configuration<T> start;
	Configuration<T> end;
	Configuration<T> current;
	std::vector<Configuration<T>> intermediate;
	
	AnimationModel(Configuration<T> _s, Configuration<T> _e) : start(_s), end(_e), current(_s) { }
	~AnimationModel() { }
};
