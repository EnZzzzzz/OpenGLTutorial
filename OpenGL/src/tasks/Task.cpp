#include "Task.h"

#include "imgui/imgui.h"

namespace task
{
	TaskMenu::TaskMenu(Task*& currentTestPtr)
		:m_CurrentTest(currentTestPtr)
	{
	}

	void TaskMenu::OnImGuiRender()
	{
		for (auto& test : m_Tests) {
			if (ImGui::Button(test.first.c_str())) {
				m_CurrentTest = test.second();
			}
		}
	}
}
