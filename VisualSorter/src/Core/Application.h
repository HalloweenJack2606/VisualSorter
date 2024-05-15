#pragma once
#include "Core/Window.h"
#include "Objects/Sorter.h"

class Application
{
public:
	Application();
	~Application();
	void Run();
private:
	Sorter m_Sorter;
	Window m_Window;
};