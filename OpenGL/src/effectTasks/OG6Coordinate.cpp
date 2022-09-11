#include "OG6Coordinate.h"

OG6Coordinate::OG6Coordinate()
{
	m_VAO = std::make_unique<VertexArray>();
	m_VAO->Bind();

    float vertices[] = {
        //     ---- 位置 ----       ---- 颜色 ----     - 纹理坐标 -
             0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // 右上
             0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // 右下
            -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // 左下
            -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // 左上
    };
    unsigned int indices[] = {
        0, 1, 3,
        1, 2, 3
    };
    m_VBO = std::make_unique<VertexBuffer>(vertices, sizeof(vertices));
    m_VBO->Bind();
    m_IBO = std::make_unique<IndexBuffer>(indices, sizeof(indices));
    m_IBO->Bind();

    m_Texture = std::make_unique<Texture>("./res/textures/wall.jpg");
}

OG6Coordinate::~OG6Coordinate()
{
}

void OG6Coordinate::OnRender()
{
}

void OG6Coordinate::OnImGuiRender()
{
}

void OG6Coordinate::OnUpdate(float deltaTime)
{
}
