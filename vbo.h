#ifndef VBO_H
#define VBO_H
// inspired by https://www.youtube.com/watch?v=NUZF_5RKfS4
#include<glm/glm.hpp>
#include "gl.h"
#include<vector>

// Structure to standardize the vertices used in the meshes
struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec4 color;
	glm::vec2 texCoord;
};



class VBO
{
public:
	// Reference ID of the Vertex Buffer Object
	GLuint m_id;
	// Constructor that generates a Vertex Buffer Object and links it to vertices
	VBO(std::vector<Vertex>& vertices);

	// Binds the VBO
	void Bind();
	// Unbinds the VBO
	void Unbind();
	// Deletes the VBO
	void Delete();
};

#endif // VBO_H