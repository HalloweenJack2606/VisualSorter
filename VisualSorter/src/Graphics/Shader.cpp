#include "Graphics/Shader.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <glm/ext.hpp>

void Shader::Create(const std::string& filePath)
{
	m_FilePath = filePath;
	CreateShader();
}

Shader::~Shader()
{
	glDeleteProgram(m_ShaderID);
}

void Shader::Bind() const
{
	glUseProgram(m_ShaderID);
}

void Shader::Unbind() const
{
	glUseProgram(0);
}

void Shader::SetInt(const std::string& name, int value)
{
	GLint location = glGetUniformLocation(m_ShaderID, name.c_str());
	glUniform1i(location, value);
}

void Shader::SetIntArray(const std::string& name, int* values, unsigned int count)
{
	GLint location = glGetUniformLocation(m_ShaderID, name.c_str());
	glUniform1iv(location, count, values);
}

void Shader::SetFloat(const std::string& name, float value)
{
	GLint location = glGetUniformLocation(m_ShaderID, name.c_str());
	glUniform1f(location, value);
}

void Shader::SetFloat2(const std::string& name, const glm::vec2& value)
{
	GLint location = glGetUniformLocation(m_ShaderID, name.c_str());
	glUniform2f(location, value.x, value.y);
}

void Shader::SetFloat3(const std::string& name, const glm::vec3& value)
{
	GLint location = glGetUniformLocation(m_ShaderID, name.c_str());
	glUniform3f(location, value.x, value.y, value.z);
}

void Shader::SetFloat4(const std::string& name, const glm::vec4& value)
{
	GLint location = glGetUniformLocation(m_ShaderID, name.c_str());
	glUniform4f(location, value.x, value.y, value.z, value.w);
}

void Shader::SetMat3(const std::string& name, const glm::mat3& value)
{
	GLint location = glGetUniformLocation(m_ShaderID, name.c_str());
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::SetMat4(const std::string& name, const glm::mat4& value)
{
	GLint location = glGetUniformLocation(m_ShaderID, name.c_str());
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::CreateShader()
{
	auto shaderSources = ReadFile(m_FilePath);

	unsigned int vertex = glCreateShader(GL_VERTEX_SHADER);
	unsigned int fragment = glCreateShader(GL_FRAGMENT_SHADER);
	//@todo: create other shaders too

	const char* vs = shaderSources[ShaderType::VERTEX].c_str();
	const char* fs = shaderSources[ShaderType::FRAGMENT].c_str();
	//const char* gs = shaderSources[GL_GEOMETRY_SHADER].c_str();

	glShaderSource(vertex, 1, &vs, nullptr);
	glShaderSource(fragment, 1, &fs, nullptr);

	glCompileShader(vertex);
	glCompileShader(fragment);
	CheckErrors(vertex, "VERTEX");
	CheckErrors(fragment, "FRAGMENT");

	m_ShaderID = glCreateProgram();

	glAttachShader(m_ShaderID, vertex);
	glAttachShader(m_ShaderID, fragment);
	glLinkProgram(m_ShaderID);

	glDeleteShader(vertex);
	glDeleteShader(fragment);

	auto lastSlash = m_FilePath.find_last_of("/\\");
	lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1;
	auto lastDot = m_FilePath.find('.');
	auto count = lastDot == std::string::npos ? m_FilePath.size() - lastSlash : lastDot - lastSlash;
	m_Name = m_FilePath.substr(lastSlash, count);
}

ShaderMap Shader::ReadFile(const std::string& filepath)
{
	ShaderType type = ShaderType::NONE;

	ShaderMap shaderSources;
	std::ifstream file(filepath);

	if (file)
	{
		std::string line;
		std::stringstream ss[3];
		while (std::getline(file, line))
		{
			if (line.find("#shader") != std::string::npos)
			{
				if (line.find("vertex") != std::string::npos) type = ShaderType::VERTEX;
				else if (line.find("fragment") != std::string::npos) type = ShaderType::FRAGMENT;
				else if (line.find("geometry") != std::string::npos) type = ShaderType::GEOMETRY;
			}
			else
			{
				ss[(int)type] << line << '\n';
			}
		}
		file.close();

		shaderSources[ShaderType::VERTEX] = ss[(int)ShaderType::VERTEX].str();
		shaderSources[ShaderType::FRAGMENT] = ss[(int)ShaderType::FRAGMENT].str();
		//shaderSources[ShaderType::GEOMETRY] = ss[(int)ShaderType::GEOMETRY].str();
	}
	else
	{
		std::cout << "Could not open file: " << filepath << std::endl;
	}

	return shaderSources;
}

void Shader::CheckErrors(const unsigned int& shader, const char* name)
{
	int status = GL_TRUE;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE)
	{
		int loglen = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &loglen);
		std::vector<char> log(loglen);
		GLsizei written = 0;
		glGetShaderInfoLog(shader, loglen, &written, log.data());
		std::cout << "Failed to compile " <<  name << " shader: " << log.data() << std::endl;
	}
}