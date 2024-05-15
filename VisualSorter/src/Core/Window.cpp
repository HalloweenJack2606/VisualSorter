#include "Window.h"
#include <iostream>

void Window::OnCreate()
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	if (!glfwInit()) std::cout << "Error initializing GLFW" << std::endl;

	m_pGLFWWindow = glfwCreateWindow(m_WindowProps.width, m_WindowProps.height, m_WindowProps.title.c_str(), nullptr, nullptr);
	glfwMakeContextCurrent(m_pGLFWWindow);

	glewExperimental = GL_TRUE;
	auto glewStatus = glewInit();
	if (glewStatus != GLEW_OK) fprintf(stderr, "Error: %s\n", glewGetErrorString(glewStatus));

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glfwSwapInterval(0);
}

void Window::OnDestroy()
{
	glfwDestroyWindow(m_pGLFWWindow);
	glfwTerminate();
}

void Window::Clear()
{
	glClear(GL_COLOR_BUFFER_BIT);
}

void Window::SwapBuffers()
{
	glfwSwapBuffers(m_pGLFWWindow);
}

void Window::PollEvents()
{
	glfwPollEvents();
}
