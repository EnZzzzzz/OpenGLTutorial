#pragma once
#include <string>
#include <vector>
#include <functional>
#include <iostream>

namespace task
{
	class Task
	{
	public:
		Task() {}
		virtual ~Task() {}

		virtual void OnUpdate(float deltaTime) {}
		virtual void OnRender() {}
		virtual void OnImGuiRender() {}
	};

	class TaskMenu: public Task
	{
	private:
		Task*& m_CurrentTest;
		std::vector<std::pair<std::string, std::function<Task*()>>> m_Tests;
	public:
		TaskMenu(Task*& currentTestPtr);

		void OnImGuiRender() override;

		template<typename T>
		void RegisterTest(const std::string& name)
		{
			std::cout << "Register test: " << name << std::endl;

			m_Tests.push_back(std::make_pair(name, []() { return new T(); }));
		}
	};
}