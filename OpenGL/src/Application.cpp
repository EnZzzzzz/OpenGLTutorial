#include <GL/glew.h> // 这个要在其它OpenGL库include之前
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

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
	
	// 第二步，调用glewInit
	if (glewInit() != GLEW_OK)
		std::cout << "Error" << std::endl;
	std::cout << glGetString(GL_VERSION) << std::endl;

	float positions[6] = {
		-0.5f, -0.5f,
		 0.0f,  0.5f,
		 0.5f, -0.5f,
	};

	unsigned int buffer;
	//创建一个vertexBuffer，
	//第一个参数是创建的buffer的数量，
	//第二参数是buffer的id,类型是GLUINT类型的（每个OpenGL对象都有一个id）
	glGenBuffers(1, &buffer);
	// 创建完buffer，需要绑定buffer，这里以array 类型的buffer绑定
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	// 绑定buffer，使用之前需要给指定buffer的数据  https://docs.gl/gl4/glBufferData
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW);
	// 告诉OpenGL data里的数据代表什么 https://docs.gl/gl4/glVertexAttribPointer
	// 第一个index是属性的index，比如定义 位置在index0，纹理在index2，法线在index3
	// size是该属性有几个数值，比如index 0定义为坐标，坐标有两个float，所以size是2
	// 用之前要enable这个属性
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
	

	// 创建shader
	std::string vertexShader;
	std::string fragmentShader;

	ShaderProgramSource source = ParseShader("res/shaders/Basic.shader");
	std::cout << "VERTEX" << std::endl;
	std::cout << source.VertexSource << std::endl;
	std::cout << "FRAGMENT" << std::endl;
	std::cout << source.FragmentSource << std::endl;

	unsigned int shader = CreateShader(source.VertexSource, source.FragmentSource);
	glUseProgram(shader);

	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		glDrawArrays(GL_TRIANGLES, 0, 3);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glDeleteProgram(shader);

	glfwTerminate();
	return 0;
}