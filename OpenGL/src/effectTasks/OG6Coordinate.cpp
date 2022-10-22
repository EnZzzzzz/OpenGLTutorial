#include "imgui/imgui.h"

#include "OG6Coordinate.h"
#include "VertexBufferLayout.h"


OG6Coordinate::OG6Coordinate()
    :m_ModelVec(glm::vec3(1.0f, 0.0f, 0.0f)), m_ViewVec(glm::vec3(0.0f, 0.0f, -3.0f)), m_Degree(-45.0f), m_PerspectDegree(45.0f)
{
	m_VAO = std::make_unique<VertexArray>();
	m_VAO->bind();

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
    m_VBO->bind();
    m_IBO = std::make_unique<IndexBuffer>(indices, sizeof(indices));
    m_IBO->Bind();

    VertexBufferLayout layout = VertexBufferLayout();
    m_VBO->layout.push<float>(3);
    m_VBO->layout.push<float>(3);
    m_VBO->layout.push<float>(2);
    m_VAO->addBuffer(*m_VBO);

    m_Texture = std::make_unique<Texture>("./res/textures/wall.jpg");
    unsigned int slot = 0;
    m_Texture->bind(slot);

    m_Shader = std::make_unique<Shader>("./res/shaders/OG6Coordinate.shader");
    m_Shader->bind();
    m_Shader->setUniform1i("ourTexture", (int)slot);
    
    
}

OG6Coordinate::~OG6Coordinate()
{

}

void OG6Coordinate::OnRender()
{
    int screenWidth = 800;
    int screenHeight = 600;
    m_Model = glm::rotate(glm::mat4(1.0f), glm::radians(m_Degree), m_ModelVec);
    m_View = glm::translate(glm::mat4(1.0f), m_ViewVec);
    m_Proj = glm::perspective(glm::radians(m_PerspectDegree), (float)screenWidth / (float)screenHeight, 0.1f, 100.0f);

    m_Shader->SetUniformMat4f("u_MVP", m_Proj * m_View * m_Model);
    m_Renderer->Draw(*m_VAO, *m_IBO, *m_Shader);
}

void OG6Coordinate::OnImGuiRender()
{
    ImGui::SliderFloat("PerpectiveDegree", &m_PerspectDegree, 0.0f, 360.0f);
    ImGui::SliderFloat("Degree", &m_Degree, -180.0f, 180.0f);
    ImGui::SliderFloat3("Model", &m_ModelVec.x, 0.0f, 1.0f);
    ImGui::SliderFloat3("view", &m_ViewVec.x, -3.0f, 3.0f);
}

void OG6Coordinate::OnUpdate(float deltaTime)
{
}
