// thank you to https://www.youtube.com/watch?v=n8t7nvHCqek
#ifndef TEXTURE_H
#define TEXTURE_H
#include <string>
#include <engine/gl.h>
class Texture
{
    private:
        GLenum m_textureTarget;
        GLuint m_textureId;
        std::string m_fileName;
    public:
        Texture(GLenum textureTarget, const std::string& fileName);

        bool Load();
        bool Load(GLint wrapS, GLint wrapT);
        void Bind(GLenum textureUnit);
};
#endif // TEXTURE_H