
#include "Display.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

Display::Display(int width, int height, const char* title)
{
	SDL_Init(SDL_INIT_EVERYTHING);

    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE,32);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,16);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,1);

	myWindow = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
	myGlContext = SDL_GL_CreateContext(myWindow);
	
	GLenum res = glewInit();
    if(res != GLEW_OK)
    {
		std::cerr << "Glew failed to initialize!" << std::endl;
    }

	myIsClosed = false;
}

Display::~Display()
{
	SDL_GL_DeleteContext(myGlContext);
	SDL_DestroyWindow(myWindow);
	SDL_Quit();
}

void Display::Clear(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

bool Display::IsClosed()
{
	return myIsClosed;
}

void Display::Update()
{
	
}
