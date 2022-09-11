#pragma once

#include <memory>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Task.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Texture.h"
#include "Renderer.h"

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
	std::unique_ptr<Renderer> m_Renderer;

	float m_Degree, m_PerspectDegree;
	glm::vec3 m_ViewVec;
	glm::vec3 m_ModelVec;

	glm::mat4 m_Model;
	glm::mat4 m_Proj;
	glm::mat4 m_View;
	glm::mat4 m_MVP;
};