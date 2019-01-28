#include "particleGenerator.h"

ParticleGenerator::ParticleGenerator(Shader& shader, Texture2D& texture, GLuint amount):shader(shader), texture(texture), amount(amount){
	this->init();
}

void ParticleGenerator::update(GLfloat dt, GameObject& object, GLuint newParticles, glm::vec2 offset){

	for(int i=0; i<newParticles; i++){
		int unusedParticle = this->firstUnusedParticle();
		this->respawnParticle(particles[unusedParticle], object, offset);
	}

	for(int i=0; i<amount; i++){
		Particle& p = this->particles[i];

		p.life -= dt* 0.005;
		if(p.life >= 0.0f){
			p.position -= p.velocity* dt* 0.01f;
			p.color.a -= dt* 0.005f;
		}
	}
}

void ParticleGenerator::draw(){
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	this->shader.use();

	glBindVertexArray(this->VAO);
	for(Particle particle: this->particles){
		if(particle.life >= 0.0f){
			this->shader.setVec("offset", particle.position);
			this->shader.setVec("color", particle.color);
			this->texture.bind();
			glDrawArrays(GL_TRIANGLES, 0, 6);
		}
	}
	glBindVertexArray(0);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}
void ParticleGenerator::init(){
	GLuint VBO;
	GLfloat particleQuad[] = {
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f,

        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f
	};
	glGenVertexArrays(1, &this->VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(particleQuad), particleQuad, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(GL_FLOAT)* 4, (void*)0);
	glBindVertexArray(0);
	for(int i=0; i<amount; i++)
		particles.push_back(Particle());
}

GLuint lastUsedParticle = 0;

GLuint ParticleGenerator::firstUnusedParticle(){

	for(int i=lastUsedParticle; i<amount; i++){
		if(this->particles[i].life <= 0.0f){
			lastUsedParticle = i;
			return i;
		}
	}

	for(int i=0; i<amount; i++){
		if(particles[i].life <= 0.0f){
			lastUsedParticle = i;
			return i;
		}
	}
	lastUsedParticle = 0;
	return 0;
}

void ParticleGenerator::respawnParticle(Particle& particle, GameObject& object, glm::vec2 offset){
	GLfloat random = (rand()%100 - 50) / 10.0f;
	GLfloat rColor = 0.5 + (rand()%100)/100.0f;
	particle.position = object.position + random + offset;
	particle.color = glm::vec4(rColor, rColor, rColor,  1.0f);
	particle.life = 1.0f;
	particle.velocity = object.velocity* 0.1f;
}