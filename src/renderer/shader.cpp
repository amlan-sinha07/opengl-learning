#include "shader.hpp"
#include "gl_helper.hpp"
#include <fstream>
#include <sstream>
#include <iostream>

Shader::Shader(const char* vertexPath,const char* fragmentPath){
    //-------------------------
    //READ VERTEX SHADER SOURCE
    //-------------------------
    std::string vertexCode;
    std::ifstream vertexFile;

    vertexFile.open(vertexPath);

    if( !vertexFile.is_open()){
        std::cerr<<"Could not open shader !! "
                <<vertexPath<<"\n";
        m_id=0;
        return;
    }
    std::stringstream vertexStream;
    vertexStream<<vertexFile.rdbuf();
    vertexFile.close();

    vertexCode=vertexStream.str();

    //-------------------------
    //READ FRAGMENT SHADER SOURCE
    //-------------------------
    std::string fragmentCode;
    std::ifstream fragmentFile;

    fragmentFile.open(fragmentPath);

    if( !fragmentFile.is_open()){
        std::cerr<<"Could not open fragment shader !! "
                <<fragmentPath<<"\n";
        m_id=0;
        return;
    }
    std::stringstream fragmentStream;
    fragmentStream<<fragmentFile.rdbuf();
    fragmentFile.close();

    fragmentCode=fragmentStream.str();

    const char* vertexSource=vertexCode.c_str();
    const char* fragmentSource=fragmentCode.c_str();


    //-----------------------------------
    //CREATE VERTEX SHADER
    //-----------------------------------
    m_id=GLHelper::createShaderProgram(vertexSource, fragmentSource);
    //GLuint vertexShader=
    /* glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader,1,&vertexSource,nullptr);
    glCompileShader(vertexShader);

    //check vertex compilation
    GLint success;
    char infoLog[512];

    glGetShaderiv(vertexShader,GL_COMPILE_STATUS,&success);

    if(!success){
        glGetShaderInfoLog(
            vertexShader,
            512,
            nullptr,
            infoLog
        );
    std::cerr<<"ERROR: Vertex shader compilation failed:\n"
    <<infoLog<<"\n";
    } */
    //----------------------
    //create fragment shader
    //----------------------
    //GLuint fragmentShader=
    /* glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(fragmentShader,1,&fragmentSource,nullptr);
    glCompileShader(fragmentShader);

    //check fragment compilation
    glGetShaderiv(fragmentShader,GL_COMPILE_STATUS,&success);
    if(!success){
        glGetShaderInfoLog(
            fragmentShader,
            512,nullptr,
            infoLog
        );
    std::cerr<<"ERROR: Fragment shader compilation failed:\n"
            <<infoLog<<"\n";
    }
    //---------------------
    //create shader program
    //---------------------
    ID=glCreateProgram();

    glAttachShader(ID,vertexShader);
    glAttachShader(ID,fragmentShader);

    glLinkProgram(ID);

    //check linking
    glGetProgramiv(ID,GL_LINK_STATUS,&success);
    if(!success){
        glGetProgramInfoLog(
                ID,
                512,
                nullptr,
                infoLog
        );
        std::cerr<<"ERROR: Shader program linking failed:\n"
                 <<infoLog<<'\n';
    }
    //once linked ,individual shaders are no longer needed
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader); */

}
void Shader::use()
{
    glUseProgram(m_id);
}
void Shader::setVec4(
    const std::string& name,
    float x,
    float y,
    float z,
    float w
)
{
    GLint location=glGetUniformLocation(m_id,name.c_str());
    if(location== -1){
        std::cerr<<"uniform not found: "<<name <<'\n';
        return;
    }
    glUniform4f(location,x,y,z,w);
}
GLuint Shader::getId() const{
    return m_id;
}
Shader::~Shader()
{
    if(m_id!=0){
        glDeleteProgram(m_id);
    }
}