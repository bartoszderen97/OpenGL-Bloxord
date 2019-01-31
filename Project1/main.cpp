#include <iostream>
#include <SDL2/SDL.h>
#include "display.h"
#include "Mesh.h"
#include "Shader.h"
#include "Transform.h"
#include "Camera.h"

static const int DISPLAY_WIDTH = 800;
static const int DISPLAY_HEIGHT = 600;

int main(int argc, char** argv)
{
	
	Display display(DISPLAY_WIDTH, DISPLAY_HEIGHT, "OpenGL");
	Vertex vert[] = {
		Vertex(glm::vec3(0.0,0.0,0.0)),
		Vertex(glm::vec3(0.0,0.5,0.0)),
		Vertex(glm::vec3(0.5,0.5,0.0)),
		Vertex(glm::vec3(0.5,0.0,0.0))

	};

	Mesh mesh(vert, sizeof(vert) / sizeof(vert[0]));
	Shader shader("./res/basicShader");
	Transform transform;
	Camera camera(glm::vec3(0, 0, -3), 70.0f, 800.0f / 600.0f, 0.01f, 1000.0f);
	transform.myRot.y = sinf(5.25f);
	float counter = 0.0f;
	while (!display.IsClosed())
	{
		display.Clear(0.5f, 0.5f, 0.5f, 1.0f);
		
		shader.Bind();
		shader.Update(transform, camera);
		mesh.Draw();

		SDL_GL_SwapWindow(display.myWindow);
		SDL_Event e;
		while (SDL_PollEvent(&e)) {

			if (e.type == SDL_QUIT) {
				display.myIsClosed = true;
			}
			else if (e.type == SDL_KEYDOWN)
			{

				counter += 0.01f;
				transform.myPos.x = sinf(counter);
				std::cout << "Key pressed \n";
			}
		}
	}
	
	return 0;
}
