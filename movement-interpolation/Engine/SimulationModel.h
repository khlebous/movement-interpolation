#pragma once
#include <glm/glm.hpp>
#include <vector>
#include <memory>
#include "Configuration.h"

template <typename T>
class SimulationModel
{
public:
	Configuration<T> start;
	Configuration<T> end;
	Configuration<T> current;
	std::vector<Configuration<T>> intermediate;
	
	SimulationModel(Configuration<T> _s, Configuration<T> _e);
	~SimulationModel() { }
};
