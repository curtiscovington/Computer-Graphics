#ifndef MATERIAL_H
#define MATERIAL_H
#include <glm/glm.hpp>
#include <engine/texture.h>
#include <engine/shader.h>

class Material
{
    private:
        Texture* m_texture;
        Texture* m_normalMap;
        Texture* m_specularMap;
        Shader* m_shader;
};  
#endif