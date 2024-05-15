#pragma once
#define GLEW_STATIC
#include <gl/glew.h>
#include <GLFW/glfw3.h>
#include "Graphics/Shader.h"

struct QuadVertex 
{
	glm::vec3 position;
	glm::vec4 color;
};

struct RenderData
{
	static constexpr unsigned int maxQuads = 5000;
	static constexpr unsigned int maxVertices = maxQuads * 4;
	static constexpr unsigned int maxIndices = maxQuads * 6;

	unsigned int VAO;
	unsigned int VBO;
	unsigned int EBO;

	unsigned int quadIndexCount = 0;

	Shader shader;

	std::vector<float> values;

	QuadVertex* quadVertexBufferBase = nullptr;
	QuadVertex* quadVertexBufferPtr = nullptr;

	glm::vec4 quadVertexPositions[4] = {};
};

class Renderer
{
public:
	static void Init();
	static void Push(const unsigned int& val, const unsigned int& max, const glm::vec4& color);
	static void Flush();
	static void Shutdown();
private:
	static RenderData s_RenderData;
};