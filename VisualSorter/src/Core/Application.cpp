#include "Core/Application.h"
#include "Graphics/Renderer.h"
#include "Core/AudioEngine.h"

Application::Application()
{
	m_Window.OnCreate();
	Renderer::Init();
	m_Sorter.Init();
	AudioEngine::Init();
}

Application::~Application()
{
	m_Window.OnDestroy();
	Renderer::Shutdown();
	AudioEngine::Shutdown();
}

void Application::Run()
{
	while (!m_Window.ShouldClose())
	{
		m_Sorter.OnUpdate();
		AudioEngine::OnUpdate();

		m_Window.Clear();
		Renderer::Flush();
		m_Window.SwapBuffers();
		m_Window.PollEvents();
	}
}
