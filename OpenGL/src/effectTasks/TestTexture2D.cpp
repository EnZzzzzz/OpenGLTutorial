#include "Renderer.h"

#include "imgui/imgui.h"
#include "glm/glm.hpp"

#include "glm/gtc/matrix_transform.hpp"
#include "TestTexture2D.h"


TestTexture2D::TestTexture2D()
    :m_Proj(glm::ortho(0.0f, 960.0f, 0.0f, 720.0f, -1.0f, 1.0f)),
    m_View(glm::translate(glm::mat4(1.0f), glm::vec3(-100, 0, 0))),
    m_TranslationA(glm::vec3(200, 200, 0)), m_TranslationB(glm::vec3(400, 200, 0))
{
    float positions[] = {
        100.0f, 100.0f, 0.0f, 0.0f, // 0
        200.0f, 100.0f, 1.0f, 0.0f,  // 1
        200.0f, 200.0f, 1.0f, 1.0f,    // 2
        100.0f, 200.0f, 0.0f, 1.0f   // 3
    };

    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    GLCall(glEnable(GL_BLEND));
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    m_VAO = std::make_unique<VertexArray>();

    m_VertexBuffer = std::make_unique<VertexBuffer>(positions, 4 * 4 * sizeof(float));
 
    m_VertexBuffer->layout.push<float>(2);
    m_VertexBuffer->layout.push<float>(2);
    m_VAO->addBuffer(*m_VertexBuffer);

    m_IndexBuffer = std::make_unique<IndexBuffer>(indices, 6);

    m_Shader = std::make_unique<Shader>("res/shaders/Basic.shader");
    m_Shader->bind();
    m_Shader->SetUniform4f("u_Color", 0.2f, 0.3f, 0.8f, 1.0f);
    m_Shader->setUniform1i("u_Texture", 0);

    m_Texture = std::make_unique<Texture>("res/textures/ChernoLogo.png");
}

TestTexture2D::~TestTexture2D()
{
    GLCall(glDisable(GL_BLEND));
}

void TestTexture2D::OnUpdate(float deltaTime)
{
}

void TestTexture2D::OnRender()
{
	GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
	GLCall(glClear(GL_COLOR_BUFFER_BIT));

    Renderer renderer;
        
    m_Texture->bind();

    {
        glm::mat4 model = glm::translate(glm::mat4(1.0f), m_TranslationA);
        glm::mat4 mvp = m_Proj * m_View * model;

        m_Shader->bind();
        m_Shader->SetUniformMat4f("u_MVP", mvp);

        renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shader);
    }

    {
        glm::mat4 model = glm::translate(glm::mat4(1.0f), m_TranslationB);
        glm::mat4 mvp = m_Proj * m_View * model;

        m_Shader->bind();
        m_Shader->SetUniformMat4f("u_MVP", mvp);

        renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shader);
    }
}

void TestTexture2D::OnImGuiRender()
{
    ImGui::SliderFloat3("m_TranslationA", &m_TranslationA.x, 0.0f, 960.0f);
    ImGui::SliderFloat3("m_TranslationB", &m_TranslationB.x, 0.0f, 960.0f);
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
}
