#ifndef SPRITE_RENDERER_H
#define SPRITE_RENDERER_H

#include <iostream>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.h"
#include "texture.h"

class SpriteRenderer{
	
	public:
		SpriteRenderer(Shader& shader);
		~SpriteRenderer();

		void drawSprite(Texture2D& texture, const glm::vec2& position, 
			const glm::vec2& size = glm::vec2(10, 10), GLfloat rotate = 0.0f, const glm::vec3& color = glm::vec3(1.0f) );
		
	private:
		Shader shader;
		GLuint quadVAO;

		void initRenderData();
};
#endif