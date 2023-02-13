#ifndef FBO_H
#define FBO_H

#include <engine/gl.h>

class FBO {
public:
	// Reference ID of the Vertex Buffer Object
	GLuint m_id;
	// Constructor that generates a Vertex Buffer Object and links it to vertices
	FBO();
    ~FBO();

	// Binds the FBO
	void Bind();
	// Unbinds the FBO
	void Unbind();
	// Deletes the FBO
	void Delete();
};

#endif // FBO_H