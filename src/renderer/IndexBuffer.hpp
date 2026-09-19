#ifndef INDEXBUFFER_HPP
#define INDEXBUFFER_HPP
class IndexBuffer{
    private:
    unsigned int m_RenderedID;
    unsigned int m_Count;
    public:
    IndexBuffer(const unsigned int* data,
                unsigned int count);
    ~IndexBuffer();

    void bind() const;
    void unbind() const;

    unsigned int getCount() const;

};
#endif