#include "Shader.h"

static void CheckErrorShader(GLuint shader, GLuint flag, bool isProgram, const char* errorMsg);
static std::string LoadShader(const std::string& fileName);
static GLuint CreateShader(const std::string& text, GLenum shaderType);

Shader::Shader(const std::string& fileName)
{
	myProgram = glCreateProgram();
	myShaders[0] = CreateShader(LoadShader(fileName + ".vs"), GL_VERTEX_SHADER);
	myShaders[1] = CreateShader(LoadShader(fileName + ".fs"), GL_FRAGMENT_SHADER);

	for (unsigned int i = 0; i < NUM_SHADERS; i++)
	{
		glAttachShader(myProgram, myShaders[i]);
	}

	glBindAttribLocation(myProgram, 0, "position");


	glLinkProgram(myProgram);
	CheckErrorShader(myProgram, GL_LINK_STATUS, true, "Error program failed to link");
	glValidateProgram(myProgram);
	CheckErrorShader(myProgram, GL_VALIDATE_STATUS, true, "Error program invalid");

	myUniforms[TRANSFORM_U] = glGetUniformLocation(myProgram, "transform");
}

void Shader::Bind()
{
	glUseProgram(myProgram);
}

void Shader::Update(Transform & transform, Camera & camera)
{
	glm::mat4 model = camera.GetViewProjection() * transform.GetModel();

	glUniformMatrix4fv(myUniforms[TRANSFORM_U], 1, GL_FALSE, &model[0][0]);
}

Shader::~Shader()
{
	for (unsigned int i = 0; i < NUM_SHADERS; i++)
	{
		glDetachShader(myProgram, myShaders[i]);
		glDeleteShader(myShaders[i]);
	}
	glDeleteProgram(myProgram);
}

void CheckErrorShader(GLuint shader, GLuint flag, bool isProgram, const char * errorMsg)
{
	GLint success = 0;
	GLchar error[1024] = { 0 };

	if (isProgram)
	{
		glGetProgramiv(shader, flag, &success);
	}
	else
	{
		glGetShaderiv(shader, flag, &success);
	}

	if (success == GL_FALSE)
	{
		if (isProgram)
		{
			glGetProgramInfoLog(shader, sizeof(error), NULL, error);
		}
		else
		{
			glGetShaderInfoLog(shader, sizeof(error), NULL, error);
		}
		std::cerr << errorMsg << ": " << error << std::endl;
	}
}

std::string LoadShader(const std::string& fileName)
{
	std::ifstream file;
	file.open(fileName);

	std::string output, line;
	if (file.is_open())
	{
		while (file.good()) {
			std::getline(file, line);
			output.append(line + "\n");
		}
	}
	else
	{
		std::cerr << "Unable to load shader: " << fileName << std::endl;
	}

	return output;
}

GLuint CreateShader(const std::string& text, GLenum shaderType)
{
	GLuint shader = glCreateShader(shaderType);

	if (shader == 0)
		std::cerr << "Error compiling shader type " << shaderType << std::endl;

	const GLchar* p[1];
	p[0] = text.c_str();
	GLint lengths[1];
	lengths[0] = text.length();

	glShaderSource(shader, 1, p, lengths);
	glCompileShader(shader);

	CheckErrorShader(shader, GL_COMPILE_STATUS, false, "Error compiling shader!");

	return shader;
}
