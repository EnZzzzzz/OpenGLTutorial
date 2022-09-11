#pragma once

#include "Task.h"


class TestClearColor : public Task
{
private:
	float m_ClearColor[4];
public:
	TestClearColor();
	~TestClearColor();

	void OnUpdate(float deltaTime) override;
	void OnRender() override;
	void OnImGuiRender() override;
};
