#pragma once

#include "Test.h"

namespace task
{

	/* �����ɫ: ָ������ָ����ɫ��䱳��ɫ ˢ�� */
	class TestClearColor : public Test
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
}