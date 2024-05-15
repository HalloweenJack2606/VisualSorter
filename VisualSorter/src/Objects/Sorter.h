#pragma once
#include <vector>
#include <glm/glm.hpp>

enum class SortingAlgorithms
{
	SELECTION,
	NONE,
};

class Sorter
{
public:
	void Init();
	void OnUpdate();
private:
	void Sort();
	void SelectionSort();
private:
	const glm::vec4 m_Red = glm::vec4(1.0f, 0.0, 0.0, 1.0f);
	const glm::vec4 m_Green = glm::vec4(0.0f, 1.0, 0.0, 1.0f);

	bool m_bFinished = false;
	glm::vec4 m_Color = m_Red;

	unsigned int m_MaxValue;
	std::vector<unsigned int> m_Values;
	SortingAlgorithms m_Algorithm = SortingAlgorithms::SELECTION;

	unsigned int m_LastIndex = 0;

	std::vector<unsigned int> m_Colored;
};
