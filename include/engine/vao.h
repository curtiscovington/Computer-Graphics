#ifndef VAO_H
#define VAO_H
// inspired by https://www.youtube.com/watch?v=NUZF_5RKfS4
#include <engine/gl.h>
#include <engine/vbo.h>

class VAO 
{
    private:
        GLuint m_id;
    
    public:
        VAO();
    
    void LinkAttrib(VBO& vbo, GLuint index, GLint size, GLenum type, GLsizei stride, GLvoid* offset);

    void Bind();
    void Unbind();
    void Delete();
};

#endif // VAO_H