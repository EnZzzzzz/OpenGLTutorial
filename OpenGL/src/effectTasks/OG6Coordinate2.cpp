#include "imgui/imgui.h"

#include "OG6Coordinate2.h"
#include "VertexBufferLayout.h"


OG6Coordinate2::OG6Coordinate2()
    :m_ModelVec(glm::vec3(1.0f, 0.0f, 0.0f)), m_ViewVec(glm::vec3(0.0f, 0.0f, -3.0f)), m_Degree(-45.0f), m_PerspectDegree(45.0f)
{
    //开启深度测试
    glEnable(GL_DEPTH_TEST);

	m_VAO = std::make_unique<VertexArray>();
	m_VAO->Bind();

    float vertices[] = {
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };
    
    m_VBO = std::make_unique<VertexBuffer>(vertices, sizeof(vertices));
    m_VBO->Bind();
    
    m_VBO->layout.Push<float>(3);
    m_VBO->layout.Push<float>(2);
    m_VAO->AddBuffer(*m_VBO);

    m_Shader = std::make_unique<Shader>("./res/shaders/OG6Coordinate2.shader");
    m_Shader->Bind();
    m_Shader->SetUniform1i("ourTexture", 0);
    m_Shader->SetUniform1i("ourTexture2", 1);

    m_Texture = std::make_unique<Texture>("./res/textures/wall.jpg");
    m_Texture2 = std::make_unique<Texture>("./res/textures/awesomeface.png");
}

OG6Coordinate2::~OG6Coordinate2()
{
    glDisable(GL_DEPTH_TEST);
}

void OG6Coordinate2::OnRender()
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // also clear the depth buffer now!
    // 纹理绑定得在循环中才行..
    m_Texture->Bind(0);
    m_Texture2->Bind(1);

    int screenWidth = 800;
    int screenHeight = 600;
    m_Model = glm::rotate(glm::mat4(1.0f), glm::radians(m_Degree), m_ModelVec);
    m_View = glm::translate(glm::mat4(1.0f), m_ViewVec);
    m_Proj = glm::perspective(glm::radians(m_PerspectDegree), (float)screenWidth / (float)screenHeight, 0.1f, 100.0f);

    m_Shader->SetUniformMat4f("u_MVP", m_Proj * m_View * m_Model);
    m_Renderer->DrawArray(*m_VAO, *m_Shader, m_VBO->GetCount());
}

void OG6Coordinate2::OnImGuiRender()
{
    ImGui::SliderFloat("PerpectiveDegree", &m_PerspectDegree, 0.0f, 360.0f);
    ImGui::SliderFloat("Degree", &m_Degree, -180.0f, 180.0f);
    ImGui::SliderFloat3("Model", &m_ModelVec.x, 0.0f, 1.0f);
    ImGui::SliderFloat3("view", &m_ViewVec.x, -3.0f, 3.0f);
}

void OG6Coordinate2::OnUpdate(float deltaTime)
{
}
