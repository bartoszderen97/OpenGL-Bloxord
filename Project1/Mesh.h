#ifndef MESH_H
#define MESH_H

#include <glm/glm.hpp>
#include <GL/glew.h>

class Vertex
{
public:
	glm::vec3 position;

	Vertex(const glm::vec3 &iPos)
	{
		position = iPos;
	}
};

class Mesh
{
public:
	Mesh(Vertex* verticles, unsigned int numVerticles);
	void Draw();
	virtual ~Mesh();

private:
	GLuint myVertexArrayObject;
	enum {
		POSITION_VB, NUM_BUFFERS
	};
	GLuint myVertexArrayBuffers[NUM_BUFFERS];
	unsigned int myDrawCount;

	Mesh(Mesh& other) {}
	void operator=(const Mesh& other) {}
};

#endif