#ifndef SHADER_HPP
#define SHADER_HPP

#include "../../dependencies/include/glad/gl.h"
#include <string>

class Shader {
    private:
        GLuint ID;
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
        GLuint getID() const;

        ~Shader();
        
};

#endif
