#include "imgui/imgui.h"

#include "OG7Camera.h"
#include "VertexBufferLayout.h"
#include "GLFW/glfw3.h"


OG7Camera::OG7Camera()
    :m_ModelVec(glm::vec3(1.0f, 0.0f, 0.0f)), m_ViewVec(glm::vec3(0.0f, 0.0f, -3.0f)), m_Degree(.0f), m_PerspectDegree(45.0f)
{
    //开启深度测试
    glEnable(GL_DEPTH_TEST);

	m_VAO = std::make_unique<VertexArray>();
	m_VAO->bind();

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
    m_VBO->bind();
    
    m_VBO->layout.push<float>(3);
    m_VBO->layout.push<float>(2);
    m_VAO->addBuffer(*m_VBO);

    m_Shader = std::make_unique<Shader>("./res/shaders/OG6Coordinate2.shader");
    m_Shader->bind();
    m_Shader->setUniform1i("ourTexture", 0);
    m_Shader->setUniform1i("ourTexture2", 1);

    m_Texture = std::make_unique<Texture>("./res/textures/wall.jpg");
    m_Texture2 = std::make_unique<Texture>("./res/textures/awesomeface.png");

    glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
    glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 cameraDirection = glm::normalize(cameraPos - cameraTarget);
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection));
    glm::vec3 cameraUp = glm::cross(cameraDirection, cameraRight);
    glm::mat4 view;
    view = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 1.0f, 0.0f));
}

OG7Camera::~OG7Camera()
{
    glDisable(GL_DEPTH_TEST);
}

void OG7Camera::OnRender()
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // also clear the depth buffer now!
    
    glm::vec3 cubePositions[] = {
          glm::vec3(0.0f,  0.0f,  0.0f),
          glm::vec3(2.0f,  5.0f, -15.0f),
          glm::vec3(-1.5f, -2.2f, -2.5f),
          glm::vec3(-3.8f, -2.0f, -12.3f),
          glm::vec3(2.4f, -0.4f, -3.5f),
          glm::vec3(-1.7f,  3.0f, -7.5f),
          glm::vec3(1.3f, -2.0f, -2.5f),
          glm::vec3(1.5f,  2.0f, -2.5f),
          glm::vec3(1.5f,  0.2f, -1.5f),
          glm::vec3(-1.3f,  1.0f, -1.5f)
    };

    m_Texture->bind(0);
    m_Texture2->bind(1);

    int screenWidth = 800;
    int screenHeight = 600;
    float radius = 10.0f;
    float camX = sin(glfwGetTime()) * radius;
    float camZ = cos(glfwGetTime()) * radius;
    glm::mat4 view;
    m_View = glm::lookAt(glm::vec3(camX, 0.0, camZ), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
    
    m_Proj = glm::perspective(glm::radians(m_PerspectDegree), (float)screenWidth / (float)screenHeight, 0.1f, 100.0f);

    for (unsigned int i = 0; i < 10; i++)
    {
        m_Model = glm::translate(glm::mat4(1.0f), cubePositions[i]);
        float angle = m_Degree * (i + 1);
        m_Model = glm::rotate(m_Model, glm::radians(angle), m_ModelVec);
        m_Shader->SetUniformMat4f("u_MVP", m_Proj * m_View * m_Model);
        m_Renderer->DrawArray(*m_VAO, *m_Shader, m_VBO->GetCount());
    }
    
}

void OG7Camera::OnImGuiRender()
{
    ImGui::SliderFloat("PerpectiveDegree", &m_PerspectDegree, 0.0f, 360.0f);
    ImGui::SliderFloat("Degree", &m_Degree, -180.0f, 180.0f);
    ImGui::SliderFloat3("Model", &m_ModelVec.x, 0.0f, 1.0f);
    ImGui::SliderFloat3("view", &m_ViewVec.x, -3.0f, 3.0f);
}

void OG7Camera::OnUpdate(float deltaTime)
{
}
