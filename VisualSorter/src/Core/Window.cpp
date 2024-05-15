#include "Window.h"
#include <iostream>

void Window::OnCreate()
{
    if (!glfwInit()) std::cout << "Error initializing GLFW" << std::endl;

    glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE );
    glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
    glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 4 );
    glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 1 );

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
