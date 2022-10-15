#include "imgui/imgui.h"

#include "Effect1Fushe.h"
#include "VertexBufferLayout.h"


Effect1Fushe::Effect1Fushe()
    :m_ModelRoaVec(glm::vec3(1.0f, 0.0f, 0.0f)), m_ViewVec(glm::vec3(0.0f, 0.0f, -3.0f)), m_Degree(0.0f), m_PerspectDegree(45.0f),
    m_ModelTraVec(glm::vec3(0.0f, 0.0f, 0.0f))
{
    glEnable(GL_DEPTH_TEST);
    m_VAO = std::make_unique<VertexArray>();
    m_VAO->Bind();

    float vertices[] = {
        //     ---- 位置 ----       ---- 颜色 ----     - 纹理坐标 -
             0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // 右上
             0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // 右下
            -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // 左下
            -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f,    // 左上
             0.0f,  0.0f, 0.0f,   1.0f, 1.0f, 1.0f,   0.5f, 0.5f    // 中心
    };
    unsigned int indices[] = {
        /*0, 1, 3,
        1, 2, 3*/
        0, 1, 4,
        1, 2, 4,
        2, 3, 4,
        3, 0, 4
    };
    m_VBO = std::make_unique<VertexBuffer>(vertices, sizeof(vertices));
    m_VBO->Bind();
    m_IBO = std::make_unique<IndexBuffer>(indices, sizeof(indices));
    m_IBO->Bind();

    VertexBufferLayout layout = VertexBufferLayout();
    m_VBO->layout.push<float>(3);
    m_VBO->layout.push<float>(3);
    m_VBO->layout.push<float>(2);
    m_VAO->AddBuffer(*m_VBO);

    m_Texture = std::make_unique<Texture>("./res/textures/wall.jpg");
    unsigned int slot = 0;
    m_Texture->Bind(slot);

    m_Shader = std::make_unique<Shader>("./res/shaders/Effect1Fushe.shader");
    m_Shader->Bind();
    m_Shader->SetUniform1i("ourTexture", (int)slot);


}

Effect1Fushe::~Effect1Fushe()
{
    glDisable(GL_DEPTH_TEST);
}

void Effect1Fushe::OnRender()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // also clear the depth buffer now!
    int screenWidth = 800;
    int screenHeight = 600;
    m_Model = glm::rotate(glm::mat4(1.0f), glm::radians(m_Degree), m_ModelRoaVec);
    m_Model = glm::translate(m_Model, m_ModelTraVec);
    m_View = glm::translate(glm::mat4(1.0f), m_ViewVec);
    m_Proj = glm::perspective(glm::radians(m_PerspectDegree), (float)screenWidth / (float)screenHeight, 0.1f, 100.0f);

    m_Shader->SetUniformMat4f("u_MVP", m_Proj * m_View * m_Model);
    m_Renderer->Draw(*m_VAO, *m_IBO, *m_Shader);
}

void Effect1Fushe::OnImGuiRender()
{
    ImGui::SliderFloat("PerpectiveDegree", &m_PerspectDegree, 0.0f, 360.0f);
    ImGui::SliderFloat("Degree", &m_Degree, -180.0f, 180.0f);
    ImGui::SliderFloat3("Model Rotatation", &m_ModelRoaVec.x, 0.0f, 1.0f);
    ImGui::SliderFloat3("Model Translation", &m_ModelTraVec.x, -10.0f, 10.0f);
    ImGui::SliderFloat3("view", &m_ViewVec.x, -3.0f, 3.0f);
}

void Effect1Fushe::OnUpdate(float deltaTime)
{
}
