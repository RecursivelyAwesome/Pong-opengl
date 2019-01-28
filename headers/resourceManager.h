#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include "shader.h"
#include "texture.h"

#include <glad/glad.h>
#include <map>
#include <fstream>
#include <sstream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class ResourceManager{
		
	public:
		//static for SDL_IMAGE INITILIZATION
		static bool isSDLImageInitialized;

		static std::map<std::string, Shader> shaders;
		static std::map<std::string, Texture2D> textures;

		static Shader loadShader(const std::string& vShaderFile, const std::string& fShaderFile,
								 const std::string& name,const std::string& gShaderFile = "");

		static Shader& getShader(const std::string& name);
		static Texture2D loadTexture(const std::string& file, GLboolean alpha, const std::string& name);
		static Texture2D& getTexture(const std::string& name);

		static void clear();

	private:
		ResourceManager(){}
		static Shader loadShaderFromFile(const std::string& vShaderFile, const std::string& fShaderFile,
								 		const std::string& gShaderFile = "" );
		static Texture2D loadTextureFromFile(const std::string& file, GLboolean alpha);


};

#endif