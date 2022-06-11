#ifndef EBO_H
#define EBO_H
#include <GL/glew.h>
#include <vector>

class EBO
{
    private:
        GLuint m_id;
    
    public:
        EBO(std::vector<GLuint>& indices);

        void Bind();
        void Unbind();
        void Delete();
};
#endif // EBO_H