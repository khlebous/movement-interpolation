#include "Axes.h"

Axes::Axes()
{
	model = glm::mat4(1);
	position = glm::vec3(0);

	GenerateBuffors();
}

Axes::~Axes()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}

void Axes::Render()
{
	shader->use();
	shader->setMat4(ShaderConstants::MODEL_MTX, glm::translate(model, position));

	glBindVertexArray(VAO);
	glDrawElements(GL_LINES, indices_size, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
	glUseProgram(0);
}

void Axes::GenerateBuffors()
{
	std::vector<glm::vec3> vert_basic =
	{
		{0.0f, 0.0f, 0.0f}, ColorConstants::RED, {1.0f, 0.0f, 0.0f}, ColorConstants::RED,
		{0.0f, 0.0f, 0.0f}, ColorConstants::GREEN, {0.0f, 1.0f, 0.0f}, ColorConstants::GREEN,
		{0.0f, 0.0f, 0.0f}, ColorConstants::BLUE, {0.0f, 0.0f, 1.0f}, ColorConstants::BLUE
	};

	std::vector<int> ind_basic = { 0, 1, 2, 3, 4, 5 };

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vert_basic.size() * 3 * sizeof(float), &vert_basic[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, ind_basic.size() * sizeof(int), &ind_basic[0], GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
