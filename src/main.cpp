#include <iostream>

#include <glad/glad.h>
#include <iomanip>

#include "game.h"


const int WIDTH = 800;
const int HEIGHT = 700;

void logError(const char* msg){
	std::cerr << msg << std::endl;
	exit(-1);
}

Game breakout(WIDTH, HEIGHT);

int main(int argc, char** argv){


	if(SDL_Init(SDL_INIT_VIDEO) < 0) exit(1);

	SDL_Window* window = SDL_CreateWindow("OPENGL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_OPENGL);
	if(window == NULL) logError("Window not created!");

	SDL_GLContext context = SDL_GL_CreateContext(window);
	if(!context) logError("Context not created!");

	//glad...like glew
	if(!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) logError("GLAD's not glad!");

	//opengl calls
	glViewport(0, 0, WIDTH, HEIGHT);
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	//Game
	breakout.init();

	//timing
	GLfloat deltaTime = 0.0f, lastFrame = 0.0f;


	bool isRunning = true;
	while(isRunning){
		GLfloat currentFrame = SDL_GetTicks();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		breakout.processInput(deltaTime);
		breakout.update(deltaTime);

		glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		breakout.render();

		SDL_GL_SwapWindow(window);
		SDL_Event e;
		while(SDL_PollEvent(&e)){

			if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)
				isRunning = false;
			breakout.updateKeys(e);
		}


	}

	ResourceManager::clear();

	SDL_DestroyWindow(window);
	return 0;
}