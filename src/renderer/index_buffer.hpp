#pragma once
#include <glad/gl.h>
class IndexBuffer{
    private:
    GLuint m_id{0};
    GLuint m_count{0};
    public:
    IndexBuffer(const unsigned int* data,
                unsigned int count);
    ~IndexBuffer();

    void bind() const;
    void unbind() const;

    GLuint getId() const;
    GLuint getCount() const;

};