#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <glad/glad.h>
#include <tuple>

#include "spriteRenderer.h"
#include "resourceManager.h"
#include "gameLevel.h"
#include "ballObject.h"
#include "particleGenerator.h"

enum class GameState{
	GAME_ACTIVE,
	GAME_MENU,
	GAME_WIN
};

enum class Direction{
	UP, DOWN, LEFT, RIGHT
};

typedef std::tuple<GLboolean, Direction, glm::vec2> Collision;

class Game{
	

	private:
		GameState state;
		GLuint width, height;
		std::vector<GameLevel> levels;
		GLuint level;
		GLboolean keys[1024];

		//managers
		SpriteRenderer* spriteRenderer;

		GLboolean checkCollision(GameObject& first, GameObject& second);
		Collision checkCollision(BallObject& first, GameObject& second);
		void doCollisions();
		Direction vectorDirection(glm::vec2 target);
	public:
		Game(GLuint width, GLuint height);
		~Game();
		//load shaders/textures/levels
		void init();

		void processInput(GLfloat dt);
		void updateKeys(SDL_Event& e);
		void update(GLfloat dt);
		void render();
		void resetLevel();
		void resetPlayer();
};

#endif