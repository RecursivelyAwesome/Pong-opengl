#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "texture.h"
#include "spriteRenderer.h"


class GameObject{

	public:
		glm::vec2 position, size, velocity;
		glm::vec3 color;

		GLfloat rotation;
		GLfloat isSolid, destroyed;

		//Render State
		Texture2D sprite;

		//Constructor
		GameObject();
		GameObject(const glm::vec2& pos, const glm::vec2& size, Texture2D& sprite, const glm::vec3& color = glm::vec3(1.0f),
					const glm::vec2& velocity = glm::vec2(0.0f));

		virtual void draw(SpriteRenderer& spriteRenderer);

};

#endif