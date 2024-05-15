#pragma once
#define GLEW_STATIC
#include <gl/glew.h>
#include <GLFW/glfw3.h>
#include <string>

struct WindowProps
{
	std::string title = "Visual Sorter";
	int width = 1280, height = 720;
};

class Window
{
public:
	void OnCreate();
	void OnDestroy();

	void Clear();
	void SwapBuffers();
	void PollEvents();

	const bool ShouldClose() const { return glfwWindowShouldClose(m_pGLFWWindow); }
private:
	GLFWwindow* m_pGLFWWindow = nullptr;
	WindowProps m_WindowProps = WindowProps();
};