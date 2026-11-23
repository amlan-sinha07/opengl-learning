#pragma once

#include <glad/gl.h>
#include <glm/glm.hpp>
#include <string>

class Shader {
private:
    GLuint m_id;
    std::unordered_map<std::string, GLint> m_uniform_loc_cache;
    [[nodiscard]] auto tryAndFindUniformfromCache([[maybe_unused]] GLuint shader_id,
                                                  std::string_view name_of_unifrom) -> GLint;

public:
    Shader(const Shader &) = default;
    Shader(Shader &&) = delete;
    auto operator=(const Shader &) -> Shader & = default;
    auto operator=(Shader &&) -> Shader & = delete;
    Shader(const char *vertexPath, const char *fragmentPath);

    void use();
    void setVec4(const std::string &name, float x, float y, float z, float w);
    void setMat4(const std::string &name, const glm::mat4 &mat);
    auto getId() const -> GLuint;

    ~Shader();
};
