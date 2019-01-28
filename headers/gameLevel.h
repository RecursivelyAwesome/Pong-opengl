#ifndef GAME_LEVEL_H
#define GAME_LEVEL_H

#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

#include "gameObject.h"
#include "resourceManager.h"

class GameLevel{
	public:
		std::vector<GameObject> bricks;	
		
		GameLevel(){}

		//load from file
		void load(const std::string& file, GLuint levelWidth, GLuint levelHeight);
		//render level
		void draw(SpriteRenderer& spriteRenderer);
		GLboolean isCompleted();

	private:
		//init level from level data
		void init(const std::vector<std::vector<GLuint>>& titleData, GLuint levelWidth, GLuint levelHeight);

};
#endif