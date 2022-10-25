#include "Renderer.h"
#include "glCheck.h"

void Renderer::Clear() const
{
    GLCall(glClear(GL_COLOR_BUFFER_BIT));
}

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
{
    shader.bind();
    va.bind();
    ib.Bind();

    GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::DrawArray(const VertexArray& va, const Shader& shader, const int count) const
{
    shader.bind();
    va.bind();
    GLCall(glDrawArrays(GL_TRIANGLES, 0, count));
}
