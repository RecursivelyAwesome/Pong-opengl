#include "resourceManager.h"

std::map<std::string, Texture2D> ResourceManager::textures;
std::map<std::string, Shader> ResourceManager::shaders;
bool ResourceManager::isSDLImageInitialized = false;

 Shader ResourceManager::loadShader(const std::string& vShaderFile, const std::string& fShaderFile,
					const std::string& name,const std::string& gShaderFile){
 	shaders[name] = loadShaderFromFile(vShaderFile, fShaderFile, gShaderFile);
 	return shaders[name];

}


 Shader& ResourceManager::getShader(const std::string& name){
 	auto iter = shaders.find(name);

 	if(iter == shaders.end())
 		std::cerr << "ERROR::" << name << " SHADER NOT FOUND" << std::endl;
	return shaders[name];

}

 Texture2D ResourceManager::loadTexture(const std::string& file, GLboolean alpha, const std::string& name){
	textures[name] = loadTextureFromFile(file, alpha);
	return textures[name];
}

 Texture2D& ResourceManager::getTexture(const std::string& name){
 	auto iter = textures.find(name);

 	if(iter == textures.end())
 		std::cerr << "ERROR::" << name << " TEXTURE NOT FOUND" << std::endl;
	return textures[name];
}


 void ResourceManager::clear(){
	for(auto iter: shaders)
		glDeleteProgram(iter.second.id);
	
	for(auto iter: textures)
		glDeleteTextures(1, &iter.second.id);
}

 Shader ResourceManager::loadShaderFromFile(const std::string& vShaderFile, const std::string& fShaderFile,
					 		const std::string& gShaderFile){
 	std::string vertexCode, fragmentCode, geometryCode;
 	try{
 		std::ifstream vertexShaderFile(vShaderFile);
 		std::ifstream fragmentShaderFile(fShaderFile);
 		std::stringstream vShaderStream, fShaderStream;

 		vShaderStream << vertexShaderFile.rdbuf();
 		fShaderStream << fragmentShaderFile.rdbuf();

 		vertexShaderFile.close();
 		fragmentShaderFile.close();

 		vertexCode = vShaderStream.str();
 		fragmentCode = fShaderStream.str();

 		if(gShaderFile != ""){
 			std::ifstream geometryShaderFile(gShaderFile);
 			std::stringstream gShaderStream;
 			gShaderStream << gShaderStream.rdbuf();
 			geometryShaderFile.close();
 			geometryCode = gShaderStream.str();
 		}
 	}
 	catch(std::exception e){
 		std::cerr << "ERROR::SHADER::FAILED TO OPEN SHADER FILES::" << vShaderFile << " " << fShaderFile <<" " << gShaderFile << std::endl;
 	}

 	Shader shader;
 	shader.compile(vertexCode, fragmentCode, geometryCode);
 	return shader;
}

 Texture2D ResourceManager::loadTextureFromFile(const std::string& file, GLboolean alpha){
 	if(!isSDLImageInitialized){
 		int flags = IMG_INIT_PNG | IMG_INIT_JPG;
 		if(IMG_Init(flags) != flags)
 			std::cerr << "SDL IMAGE NOT INITIALIZED!" << std::endl;
 		ResourceManager::isSDLImageInitialized = true;
 	}

 	Texture2D texture;
 	if(alpha){
 		texture.internalFormat = GL_RGBA;
 		texture.imageFormat = GL_RGBA;
 	}
 	int width, height;
 	SDL_Surface* image = IMG_Load(file.c_str());
 	if(image == NULL) std::cerr << "ERROR::IMAGE::" << file << " NOT FOUND!" << std::endl;
 	else{
	 	texture.generate(image->w, image->h, (unsigned char*)image->pixels);
	 	SDL_FreeSurface(image);
	 }
 	return texture;
}