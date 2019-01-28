#include "spriteRenderer.h"


SpriteRenderer::SpriteRenderer(Shader& shader): shader(shader){
		this->initRenderData();
}

SpriteRenderer::~SpriteRenderer(){
	glDeleteVertexArrays(1, &this->quadVAO);
	
}

void SpriteRenderer::drawSprite(Texture2D& texture, const glm::vec2& position, 
								const glm::vec2& size, GLfloat rotate , const glm::vec3& color ){
	
	this->shader.use();

	glm::mat4 model;
	model = glm::translate(model, glm::vec3(position, 0.0f));

	model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f)); 
    model = glm::rotate(model, rotate, glm::vec3(0.0f, 0.0f, 1.0f)); 
    model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));

	model = glm::scale(model, glm::vec3(size, 1.0f));

	this->shader.setMatrix4("model", model);
	this->shader.setVec("spriteColor", color);

	glActiveTexture(GL_TEXTURE0);
	texture.bind();

	glBindVertexArray(this->quadVAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);	
	glBindVertexArray(0);

}

void SpriteRenderer::initRenderData(){
		
		GLuint VBO;
		GLfloat vertices[] = {
			0.0f, 1.0f, 0.0f, 1.0f,
			1.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 0.0f,

			 0.0f, 1.0f, 0.0f, 1.0f,
	        1.0f, 1.0f, 1.0f, 1.0f,
	        1.0f, 0.0f, 1.0f, 0.0f
		};

		glGenVertexArrays(1, &this->quadVAO);
		glGenBuffers(1, &VBO);

		glBindVertexArray(this->quadVAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(GL_FLOAT)* 4, (GLvoid*)0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);


}