#ifndef TEXTURE_H
#define TEXTURE_H

#include <iostream>
#include <glad/glad.h>

class Texture2D{

	public:
		GLuint id;

		GLuint width, height;

		GLuint internalFormat, imageFormat;

		GLuint wrapS, wrapT, filterMin, filterMax;

		Texture2D();

		void generate(GLuint width, GLuint height, unsigned char* data);
		void bind() const;
};
#endif