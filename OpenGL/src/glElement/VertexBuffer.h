#pragma once

#include "VertexBufferLayout.h"

class VertexBuffer
{
private:
	unsigned int m_RendererID;
	int m_Size;
	
public:
	VertexBuffer(const void* data, unsigned int size);
	~VertexBuffer();

	void bind() const;
	void Unbind() const;
	int GetCount();
	VertexBufferLayout layout;
};