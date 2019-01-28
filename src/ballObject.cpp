#include "ballObject.h"


BallObject::BallObject(): GameObject(), radius(12.5f), stuck(true){
}

BallObject::BallObject(const glm::vec2& pos, GLfloat radius, const glm::vec2& velocity, Texture2D& sprite):
	GameObject(pos, glm::vec2(2* radius), sprite, glm::vec3(1.0f), velocity), radius(radius), stuck(true)
{
}


glm::vec2 BallObject::move(GLfloat dt, GLuint windowWidth){
	if(!this->stuck){

		this->position += this->velocity* dt;
		if(this->position.x <= 0.0f){
			this->velocity.x *= -1;
			this->position.x = 0;
		}
		else if(this->position.x + this->size.x >= windowWidth){
			this->velocity.x *= -1;
			this->position.x = windowWidth - this->size.x;
		}
		if(this->position.y <= 0.0f){
			this->velocity.y *= -1;
			this->position.y = 0.0f;
		}
	}
	return this->position;
}

void BallObject::reset(const glm::vec2& position, const glm::vec2& velocity){
	this->position = position;
	this->velocity = velocity;
	this->stuck = true;
}