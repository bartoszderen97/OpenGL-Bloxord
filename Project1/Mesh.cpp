#include "Mesh.h"

Mesh::Mesh(Vertex* verticles, unsigned int numVerticles)
{
	myDrawCount = numVerticles;
	glGenVertexArrays(1, &myVertexArrayObject);
	glBindVertexArray(myVertexArrayObject);

	glGenBuffers(NUM_BUFFERS, myVertexArrayBuffers);
	glBindBuffer(GL_ARRAY_BUFFER, myVertexArrayBuffers[POSITION_VB]);
	glBufferData(GL_ARRAY_BUFFER, myDrawCount * sizeof(verticles[0]), verticles, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);


	glBindVertexArray(0);
}

void Mesh::Draw()
{
	glBindVertexArray(myVertexArrayObject);
	glDrawArrays(GL_QUADS, 0, myDrawCount);
	glBindVertexArray(0);
}


Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &myVertexArrayObject);
}
