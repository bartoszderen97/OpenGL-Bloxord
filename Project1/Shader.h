#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <string>
#include <fstream>
#include <iostream>
#include "Transform.h"
#include "Camera.h"

class Shader
{
public:
	Shader(const std::string& fileName);
	void Bind();
	void Update(Transform& transforms, Camera& camera);
	virtual ~Shader();

private:
	enum
	{
		TRANSFORM_U,
		NUM_UNIFORMS
	};
	static const unsigned int NUM_SHADERS = 2;
	GLuint myProgram;
	GLuint myShaders[NUM_SHADERS];
	GLuint myUniforms[NUM_UNIFORMS];
	

	Shader(Shader& other) {}
	void operator=(const Shader& other) {}
};


#endif // !SHADER_H