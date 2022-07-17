#include <GL/glew.h> // 这个要在其它OpenGL库include之前
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"

//#define ASSERT(x) if (!(x)) __debugbreak(); //#设置一个宏，如果出错就会打一个断点
//#define GLCall(x) GLClearError();\
//	x;\
//	ASSERT(GLLogCall(#x, __FILE__, __LINE__))


struct ShaderProgramSource
{
	std::string VertexSource;
	std::string FragmentSource;
};

static ShaderProgramSource ParseShader(const std::string& filePath)
{
	std::ifstream stream(filePath);
	enum class ShaderType
	{
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};

	std::string line;
	std::stringstream ss[2];
	ShaderType type = ShaderType::NONE;
	while (getline(stream, line))
	{
		if (line.find("#shader") != std::string::npos)
		{
			if (line.find("vertex") != std::string::npos)
			{
				type = ShaderType::VERTEX;
			}
			else if (line.find("fragment") != std::string::npos)
			{
				type = ShaderType::FRAGMENT;
			}
		}
		else
		{
			ss[int(type)] << line << '\n';
		}
	}
	return { ss[0].str(), ss[1].str() };
}

static unsigned int CompileShader(unsigned int type, const std::string& source)
{
	// 创建shader第二步，创建一个shader id，用于绑定
	unsigned int id = glCreateShader(type);
	const char * src = source.c_str();  // 或者写source.c_str();
	// 创建glShaderSource https://docs.gl/gl4/glShaderSource
	glShaderSource(id, 1, &src, nullptr);
	// 然后compile就行了
	glCompileShader(id);

	// 编译状态检查
	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		// C++ 处理动态数组的小技巧, alloca 在栈区申请一块长度的内存
		char* message = (char*) alloca(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, message);
		std::cout << "Failed to compile shader "
			      << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") 
			      <<" shader " << std::endl;
		return 0;
	}
	else
	{
		std::cout << "Successed to compile shader "
			<< (type == GL_VERTEX_SHADER ? "vertex" : "fragment")
			<< " shader " << std::endl;
	}

	return id;
}

static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
	// 创建shader第一步，创建一个program
	unsigned int program = glCreateProgram();
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);
	// 然后把这两个shader attach进program
	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	// link完program以后，就可以删除shader了
	glDeleteShader(vs);
	glDeleteShader(fs);
	return program;
}


int main(void)
{
	GLFWwindow* window;

	if (!glfwInit())
	{
		return -1;
	}

	window = glfwCreateWindow(640, 480, "Hellow World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	// 第一步，创建OpenGL渲染上下文
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1); // 与显示器的刷新率保持一致（垂直同步）
	
	// 第二步，调用glewInit
	if (glewInit() != GLEW_OK)
		std::cout << "Error" << std::endl;
	std::cout << glGetString(GL_VERSION) << std::endl;

	float positions[] = {
		-0.5f, -0.5f,
		 0.5f, -0.5f,
		 0.5f,  0.5f,
		-0.5f,  0.5f
	};

	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	unsigned int vao;
	GLCall(glGenVertexArrays(1, &vao));
	GLCall(glBindVertexArray(vao));

	VertexArray va;
	VertexBuffer vb(positions, 4 * 2 * sizeof(float)); //这里positions是一个数组，但是以const void* 的形式传入了？？
	VertexBufferLayout layout;
	layout.push<float>(2);
	va.AddBuffer(vb, layout);
	
	IndexBuffer ib(indices, 6);	

	// 创建shader
	std::string vertexShader;
	std::string fragmentShader;

	ShaderProgramSource source = ParseShader("res/shaders/Basic.shader");
	/*std::cout << "VERTEX" << std::endl;
	std::cout << source.VertexSource << std::endl;
	std::cout << "FRAGMENT" << std::endl;
	std::cout << source.FragmentSource << std::endl;*/

	unsigned int shader = CreateShader(source.VertexSource, source.FragmentSource);
	glUseProgram(shader);

	GLCall(int location = glGetUniformLocation(shader, "u_Color"));
	ASSERT(location != -1); //shader编译器在编译的时候会去掉没有用到的变量，所以要做一个变量检测

	GLCall(glBindVertexArray(0));
	GLCall(glUseProgram(0));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));

	float r = 0.0f;
	float increment = 0.05f;

	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		GLCall(glUseProgram(shader));
		GLCall(glUniform4f(location, r, 0.3f, 0.8f, 1.0f));

		va.Bind();
		ib.Bind();

		//glDrawArrays(GL_TRIANGLES, 0, 6);
		GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

		if (r > 1.0f)
		{
			increment = -0.05f;
		}
		else if (r < 0.0f)
		{
			increment = 0.05f;
		}
		r += increment;

		/* Swap front and back buffers */
		GLCall(glfwSwapBuffers(window));

		/* Poll for and process events */
		glfwPollEvents();
	}

	glDeleteProgram(shader);

	glfwTerminate();
	return 0;
}