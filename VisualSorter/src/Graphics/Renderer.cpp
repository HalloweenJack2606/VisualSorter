#include "Renderer.h"
#include <glm/gtx/transform.hpp>

RenderData Renderer::s_RenderData;

namespace lol {}

void Renderer::Init()
{
	s_RenderData.shader.Create("assets/shaders/default.glsl");

	glGenVertexArrays(1, &s_RenderData.VAO);
	glGenBuffers(1, &s_RenderData.VBO);	

	glBindVertexArray(s_RenderData.VAO);
	glBindBuffer(GL_ARRAY_BUFFER, s_RenderData.VBO);

	//VBO
	glBufferData(GL_ARRAY_BUFFER, s_RenderData.maxVertices * sizeof(QuadVertex), nullptr, GL_DYNAMIC_DRAW);

	//EBO
	unsigned int* quadIndices = new unsigned int[s_RenderData.maxIndices];
	unsigned int offset = 0;

	for (unsigned int i = 0; i < s_RenderData.maxIndices; i += 6)
	{
		quadIndices[i + 0] = offset + 0;
		quadIndices[i + 1] = offset + 1;
		quadIndices[i + 2] = offset + 2;

		quadIndices[i + 3] = offset + 2;
		quadIndices[i + 4] = offset + 3;
		quadIndices[i + 5] = offset + 0;

		offset += 4;
	}

	glGenBuffers(1, &s_RenderData.EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, s_RenderData.EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * s_RenderData.maxIndices, quadIndices, GL_STATIC_DRAW);
	delete[] quadIndices;

	//VAO
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	s_RenderData.quadVertexBufferBase = new QuadVertex[s_RenderData.maxVertices];
	s_RenderData.quadVertexBufferPtr = s_RenderData.quadVertexBufferBase;

	s_RenderData.quadVertexPositions[0] = { -0.5f, -0.5f, 0.0f, 1.0f };
	s_RenderData.quadVertexPositions[1] = {  0.5f, -0.5f, 0.0f, 1.0f };
	s_RenderData.quadVertexPositions[2] = {  0.5f,  0.5f, 0.0f, 1.0f };
	s_RenderData.quadVertexPositions[3] = { -0.5f,  0.5f, 0.0f, 1.0f };
}

void Renderer::Push(const unsigned int& val, const unsigned int& max, const glm::vec4& color)
{
	const float margin = 0.05f;
	const float space = 2.0f;
	float maxSpace = space - margin * 2;
	float spacePerLine = maxSpace / (max - 1);
	const float start = 0 - 1.0f + margin;
	const int index = (int)s_RenderData.quadIndexCount / 6;
	const float maxHeight = 2.0f;
	float height = val * (maxHeight / max);


	glm::vec3 position(start + index * spacePerLine, -1.0f + height / 2.0f, 0.0f);
	glm::vec3 scale(spacePerLine, height, 1.0f);

	glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), scale);

	static constexpr int quadVertexCount = 4;
	for (int i = 0; i < quadVertexCount; i++)
	{
		s_RenderData.quadVertexBufferPtr->position = transform * s_RenderData.quadVertexPositions[i];
		s_RenderData.quadVertexBufferPtr->color = color;
		s_RenderData.quadVertexBufferPtr++;
	}

	s_RenderData.quadIndexCount += 6;
}

void Renderer::Flush()
{
	s_RenderData.shader.Bind();

	unsigned int dataSize = (unsigned int)((unsigned char*)s_RenderData.quadVertexBufferPtr - (unsigned char*)s_RenderData.quadVertexBufferBase);
	glBufferSubData(GL_ARRAY_BUFFER, 0, dataSize, s_RenderData.quadVertexBufferBase);

	glDrawElements(GL_TRIANGLES, s_RenderData.quadIndexCount, GL_UNSIGNED_INT, nullptr);
	s_RenderData.shader.Unbind();

	s_RenderData.quadIndexCount = 0;
	s_RenderData.quadVertexBufferPtr = s_RenderData.quadVertexBufferBase;
}

void Renderer::Shutdown()
{
	glDeleteVertexArrays(1, &s_RenderData.VAO);
	glDeleteBuffers(1, &s_RenderData.VBO);
	glDeleteBuffers(1, &s_RenderData.EBO);
}
