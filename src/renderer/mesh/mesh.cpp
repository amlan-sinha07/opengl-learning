#include "mesh.hpp"

#include "../../core/logging/logger.hpp"

#include <stdexcept>
#include <utility>

Mesh::Mesh(const std::vector<MeshVertex> &vertices, const std::vector<unsigned int> &indices,
           GLenum primitiveMode)
    : m_vbo(vertices.data(), static_cast<GLsizeiptr>(vertices.size() * sizeof(MeshVertex))),
      m_ebo(indices.data(), static_cast<unsigned int>(indices.size())),
      m_primitiveMode(primitiveMode) {
    if (vertices.empty()) {
        throw std::invalid_argument("Mesh: vertex list is empty");
    }

    if (indices.empty()) {
        throw std::invalid_argument("Mesh: index list is empty");
    }

    // An attribute that exists in the struct but is all zeros still needs a layout
    // entry, otherwise the stride is wrong for every attribute after it.
    //
    // Offsets and component counts come from MeshVertex itself, so a typo in a field
    // name fails to compile instead of quietly shifting every later attribute. The
    // KASSERT catches a field that was never listed here at all.
    BufferLayout Layout(attribute("v3_inPosition", &MeshVertex::Position),
                        attribute("v3_inColor", &MeshVertex::Color),
                        attribute("v3_inNormal", &MeshVertex::Normal));

    KASSERT(Layout.getStride() == static_cast<GLsizei>(sizeof(MeshVertex)),
            "BufferLayout must describe every field of MeshVertex");

    m_vao.bind();

    m_vao.addVertexBuffer(m_vbo, Layout);

    m_ebo.bind();

    m_vao.unbind();
    m_ebo.unbind();
}

// Moving allowed
Mesh::Mesh(Mesh &&other) noexcept
    : m_vao(std::move(other.m_vao)),
      m_vbo(std::move(other.m_vbo)),
      m_ebo(std::move(other.m_ebo)),
      m_primitiveMode(other.m_primitiveMode) {}

auto Mesh::operator=(Mesh &&other) noexcept -> Mesh & {
    if (this != &other) {
        m_vao = std::move(other.m_vao);
        m_vbo = std::move(other.m_vbo);
        m_ebo = std::move(other.m_ebo);
        m_primitiveMode = other.m_primitiveMode;
    }
    return *this;
}

void Mesh::bind() const {
    m_vao.bind();
    m_ebo.bind();
}

void Mesh::unbind() const {
    m_ebo.unbind();
    m_vao.unbind();
}

void Mesh::updateVertices(const std::vector<MeshVertex> &vertices) {
    m_vbo.update(vertices.data(), static_cast<GLsizeiptr>(vertices.size() * sizeof(MeshVertex)));
}

GLuint Mesh::getVAO() const { return m_vao.getId(); }

GLuint Mesh::getEBO() const { return m_ebo.getId(); }

GLsizei Mesh::getIndexCount() const { return static_cast<GLsizei>(m_ebo.getCount()); }

GLenum Mesh::getPrimitiveMode() const { return m_primitiveMode; }