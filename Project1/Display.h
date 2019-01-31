#ifndef DISPLAY_H
#define DISPLAY_H

#include <string>
#include <SDL2/SDL.h>

class Display
{
public:
	Display(int width, int height, const char* title);
	void Update();
	void Clear(float r, float b, float g, float a);
	bool IsClosed();
	virtual ~Display();

	SDL_Window* myWindow;
	bool myIsClosed;

private:
	SDL_GLContext myGlContext;

	Display(Display& other){}
	void operator=(const Display& other) {}
};


#endif // !DISPLAY_H

