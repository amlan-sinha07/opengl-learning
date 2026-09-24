#pragma once

#include <glad/gl.h>
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
        GLuint getId() const;

        ~Shader();

};
