#include "SimulationView.h"

SimulationModel::SimulationModel() : 
	startPos(glm::vec3(0)), endPos(glm::vec3(2, 1, 0))
{
	isRunning = false;
	currentTime = 0.0f;
	animationTime = 3.0f;
}
