#include "Axes.h"
#include "Constnants/VectorConstants.h"

Axes::Axes()
{
	model = glm::mat4(1);

	GenerateBuffors();
}

Axes::~Axes()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}

void Axes::Render(glm::vec3 pos, glm::vec3 rot, float opacity)
{
	shader->use();

	glm::mat4 m_model;

	float rad_x = glm::radians(rot.x);
	float s1 = glm::sin(rad_x);
	float c1 = glm::cos(rad_x);
	float rad_y = glm::radians(rot.y);
	float s2 = glm::sin(rad_y);
	float c2 = glm::cos(rad_y);
	float rad_z = glm::radians(rot.z);
	float s3 = glm::sin(rad_z);
	float c3 = glm::cos(rad_z);

	m_model = glm::transpose(glm::mat4(c2 * c3, -s2, c2 * s3, pos.x,
		s1 * s3 + c1 * c3 * s2, c1 * c2, c1 * s2 * s3 - c3 * s1, pos.y,
		c3 * s1 * s2 - c1 * s3, c2 * s1, c1 * c3 + s1 * s2 * s3, pos.z,
		0, 0, 0, 1));

	/*m_model = glm::translate(glm::mat4(1), pos);

	m_model = glm::rotate(m_model, glm::radians(rot.x), VectorConstants::V_RIGHT);
	m_model = glm::rotate(m_model, glm::radians(rot.y), VectorConstants::V_UP);
	m_model = glm::rotate(m_model, glm::radians(rot.z), VectorConstants::V_FORWARD);*/

	shader->setMat4(ShaderConstants::MODEL_MTX, m_model);
	shader->setFloat(ShaderConstants::OPACITY, opacity);

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
