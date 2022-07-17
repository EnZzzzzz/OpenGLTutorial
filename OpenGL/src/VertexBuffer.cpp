#include "VertexBuffer.h"
#include "Renderer.h"


VertexBuffer::VertexBuffer(const void * data, unsigned int size)
{
	//绑定buffer就是把数据从cpu发到gpu
	//创建一个vertexBuffer，
	//第一个参数是创建的buffer的数量，
	//第二参数是buffer的id,类型是GLUINT类型的（每个OpenGL对象都有一个id）
	GLCall(glGenBuffers(1, &m_RendererID));
	// 创建完buffer，需要绑定buffer，这里以array 类型的buffer绑定
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
	// 绑定buffer，使用之前需要给指定buffer的数据  https://docs.gl/gl4/glBufferData
	GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

VertexBuffer::~VertexBuffer()
{
	GLCall(glDeleteBuffers(1, &m_RendererID));
}

void VertexBuffer::Bind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
}

void VertexBuffer::Unind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
