#include "Objects/Sorter.h"
#include <iostream>
#include <random>
#include <algorithm>
#include "Graphics/Renderer.h"
#include "Core/AudioEngine.h"

void Sorter::Init()
{
	m_MaxValue = 1000;
	m_Values.clear();
	m_Values.reserve(m_MaxValue);
	for (unsigned int i = 1; i <= m_MaxValue; i++)
	{
		m_Values.push_back(i);
	}
	auto rd = std::random_device{};
	auto rng = std::default_random_engine{rd()};
	std::shuffle(m_Values.begin(), m_Values.end(), rng);
}

void Sorter::OnUpdate()
{
	Sort();
	for (const auto& it : m_Values)
	{
		auto found = std::find(m_Colored.begin(), m_Colored.end(), it);
		glm::vec4 color(1.0f, 1.0f, 1.0f, 1.0f);
		if (found != m_Colored.end()) color = m_Color;
		Renderer::Push(it, m_MaxValue, color);
	}
}

void Sorter::Sort()
{
	if (!m_bFinished)
	{
		if (m_LastIndex < m_MaxValue)
		{
			switch (m_Algorithm)
			{
			case SortingAlgorithms::SELECTION:
				SelectionSort();
				break;
			case SortingAlgorithms::NONE:
				break;
			}
		}
		else
		{
			m_bFinished = true;
			m_LastIndex = 0;
			m_Colored.clear();
			m_Color = m_Green;
		}
	}
	else
	{
		static bool play = true;
		if (play)
		{
			play = false;
			AudioEngine::Play(1);
		}
		for(int i = 0; i < m_MaxValue / 100; i++) m_Colored.push_back(m_LastIndex + i);
		m_LastIndex += m_MaxValue / 100;

	}
}

void Sorter::SelectionSort()
{
	auto smallestIndex = m_LastIndex;
	const unsigned int prev = m_Values[smallestIndex];

	for (int i = m_LastIndex; i < m_Values.size(); i++)
	{
		if (m_Values[i] < m_Values[smallestIndex]) smallestIndex = i;
	}

	m_Values[m_LastIndex] = m_Values[smallestIndex];
	m_Values[smallestIndex] = prev;

	m_Colored.clear();
	m_Colored.push_back(m_LastIndex);
	m_Colored.push_back(smallestIndex);

	static bool yes = true;
	if (yes)
	{
		yes = false;
	}
	AudioEngine::Play(0);

	m_LastIndex++;
}