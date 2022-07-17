#pragma once
#include <iostream>

#include <GL/glew.h> // 这个要在其它OpenGL库include之前

#define ASSERT(x) if (!(x)) __debugbreak(); //#设置一个宏，如果出错就会打一个断点
#define GLCall(x) GLClearError();\
	x;\
	ASSERT(GLLogCall(#x, __FILE__, __LINE__))


void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);