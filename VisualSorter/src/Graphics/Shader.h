#pragma once
#include <unordered_map>
#include <glm/glm.hpp>
#include <string>
#include <iostream>
#define GLEW_STATIC
#include <gl/glew.h>

enum class ShaderType
{
	NONE = 0,

	VERTEX = 1,
	FRAGMENT = 2,
	GEOMETRY = 3
};

typedef std::unordered_map<ShaderType, std::string> ShaderMap;
class Shader
{
public:
	Shader() = default;
	~Shader();

	void Create(const std::string& filePath);

	void Bind() const;
	void Unbind() const;

	void SetInt(const std::string& name, int value);
	void SetIntArray(const std::string& name, int* values, unsigned int count);
	void SetFloat(const std::string& name, float value);
	void SetFloat2(const std::string& name, const glm::vec2& value);
	void SetFloat3(const std::string& name, const glm::vec3& value);
	void SetFloat4(const std::string& name, const glm::vec4& value);
	void SetMat3(const std::string& name, const glm::mat3& value);
	void SetMat4(const std::string& name, const glm::mat4& value);

	const std::string& GetName() const { return m_Name; }
	const std::string& GetPath() const { return m_FilePath; }
private:
	void CreateShader();

	ShaderMap ReadFile(const std::string& filepath);
	void CheckErrors(const unsigned int& shader, const char* name);
private:
	unsigned int m_ShaderID;
	std::string m_FilePath;
	std::string m_Name;
};