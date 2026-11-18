#pragma once

#include <glad/gl.h>
#include <glm/glm.hpp>
#include <string>

class Shader {
    private:
        GLuint m_id;
    public:
        Shader(const char* vertexPath,const char* fragmentPath);

        void use();
        void setVec4(
            const std::string& name ,
            float x,
            float y,
            float z,
            float w
        );
        void setMat4(const std::string& name, const glm::mat4& mat);
        GLuint getId() const;

        ~Shader();

};
