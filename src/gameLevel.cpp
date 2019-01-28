#include "gameLevel.h"

void GameLevel::load(const std::string& file, GLuint levelWidth, GLuint levelHeight){
	//load level from a file
	this->bricks.clear();

	GLuint tileCode;
	GameLevel level;

	std::string line;
	std::ifstream fstream(file);
	std::vector<std::vector<GLuint>> tileData;
	if(fstream){
		while(std::getline(fstream, line)){
			std::istringstream ss(line);
			std::vector<GLuint> row;
			while(ss >> tileCode) row.push_back(tileCode);
			tileData.push_back(row);
		}
		if(tileData.size() > 0)
			this->init(tileData, levelWidth, levelHeight);
	}else
		std::cerr << "ERROR::" << file << " LEVEL NOT FOUND" << std::endl;

}

void GameLevel::draw(SpriteRenderer& spriteRenderer){

	for(GameObject& tile: bricks){
		if(!tile.destroyed)
			tile.draw(spriteRenderer);
	}

}

GLboolean GameLevel::isCompleted(){
	for(GameObject& tile: bricks){
		if(!tile.isSolid && !tile.destroyed)
			return GL_FALSE;
	}
	return GL_TRUE;
}

void GameLevel::init(const std::vector<std::vector<GLuint>>& tileData, GLuint levelWidth, GLuint levelHeight){
	//calculate dimensions
	GLuint height = tileData.size();
	GLuint width = tileData[0].size();
	GLfloat unitWidth = levelWidth/static_cast<GLfloat>(width);
	GLfloat unitHeight = levelHeight/static_cast<GLfloat>(height);

	for(GLuint y=0; y< height; y++){
		for(GLuint x=0; x<width; x++){
			if(tileData[y][x] == 1){
				//SOLID TILE
				glm::vec2 pos(unitWidth* x, unitHeight*y);
				glm::vec2 size(unitWidth, unitHeight);
				GameObject obj(pos, size, ResourceManager::getTexture("block_solid"), glm::vec3(0.8f, 0.8f, 0.7f))	;
				obj.isSolid = true;
				this->bricks.push_back(obj);
			}
			else if(tileData[y][x] > 0){
				glm::vec3 color(1.0f);
				GLuint tileType = tileData[y][x];
				switch(tileType){
					case 2:
						color = glm::vec3(0.2f, 0.6f, 1.0f);
						break;
					case 3:
						color = glm::vec3(0.0f, 0.7f, 0.0f);
						break;
					case 4:
						color = glm::vec3(0.8f, 0.8f, 0.4f);
						break;
					case 5:
						color = glm::vec3(1.0f, 0.5f, 0.0f);
						break;
				}
				glm::vec2 pos(x* unitWidth, y* unitHeight);
				glm::vec2 size(unitWidth, unitHeight);
				this->bricks.push_back(GameObject(pos, size, ResourceManager::getTexture("block"), color));
			}
		}
	}

}
