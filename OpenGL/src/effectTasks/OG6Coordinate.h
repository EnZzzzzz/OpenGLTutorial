#pragma once

#include <memory>

#include "Task.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Texture.h"

class OG6Coordinate : public Task
{
public:
	OG6Coordinate();
	~OG6Coordinate();
	void OnRender() override;
	void OnImGuiRender() override;
	void OnUpdate(float deltaTime) override;

private:
	std::unique_ptr<VertexArray> m_VAO;
	std::unique_ptr<VertexBuffer> m_VBO;
	std::unique_ptr<IndexBuffer> m_IBO;
	std::unique_ptr<Shader> m_Shader;
	std::unique_ptr<Texture> m_Texture;
};