#ifndef BALL_OBJECT_H
#define BALL_OBJECT_H


#include "gameObject.h"

class BallObject: public GameObject{
	
	public:
		GLfloat radius;
		GLboolean stuck;

		BallObject();
		BallObject(const glm::vec2& pos, GLfloat radius, const glm::vec2& velocity, Texture2D& sprite);

		glm::vec2 move(GLfloat dt, GLuint windowWidth);
		void reset(const glm::vec2& position, const glm::vec2& velocity);

};

#endif