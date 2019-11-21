#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <memory>

#include "Shader.h"
#include "Constnants/ColorConstants.h"

class Axes
{
	unsigned int VAO, VBO, EBO;
	std::shared_ptr<Shader> shader;
	glm::mat4 model;
	glm::vec3 position;

	const int indices_size = 6;

public:
	Axes();
	~Axes();

	void SetShader(std::shared_ptr<Shader> _s) { shader = _s; }

	void Render();

private:
	void GenerateBuffors();
};
