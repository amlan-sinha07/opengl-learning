#include "mesh.hpp"

#include <stdexcept>

Mesh::Mesh(const std::vector<Vertex> &vertices, const std::vector<unsigned int> &indices,
           GLenum primitiveMode)
    : m_vbo(vertices.data(), static_cast<GLsizeiptr>(vertices.size() * sizeof(Vertex))),
      m_ebo(indices.data(), static_cast<unsigned int>(indices.size())),
      m_primitiveMode(primitiveMode) {
    if (vertices.empty()) {
        throw std::invalid_argument("Mesh: vertex list is empty");
    }

    if (indices.empty()) {
        throw std::invalid_argument("Mesh: index list is empty");
    }

    BufferLayout Layout{{"v3_Position", GL_FLOAT, 3, GL_FALSE},
                        {"v3_Color", GL_FLOAT, 3, GL_FALSE},};

    m_vao.bind();

    m_vao.addVertexBuffer(m_vbo, Layout);

    m_ebo.bind();

    m_vao.unbind();
    m_ebo.unbind();
}

void Mesh::bind() const {
    m_vao.bind();
    m_ebo.bind();
}

void Mesh::unbind() const {
    m_ebo.unbind();
    m_vao.unbind();
}

void Mesh::updateVertices(const std::vector<Vertex>& vertices) {
    m_vbo.update(vertices.data(), static_cast<GLsizeiptr>(vertices.size() * sizeof(Vertex)));
}

GLuint Mesh::getVAO() const { return m_vao.getId(); }

GLuint Mesh::getEBO() const { return m_ebo.getId(); }

GLsizei Mesh::getIndexCount() const { return static_cast<GLsizei>(m_ebo.getCount()); }

GLenum Mesh::getPrimitiveMode() const { return m_primitiveMode; }