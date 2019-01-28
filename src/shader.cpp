#include "shader.h"

void Shader::compile(const std::string& vertexSource, const std::string& fragmentSource, const std::string& geometrySource ){
	//compile shaders
	GLuint vShader, fShader, gShader;


	//vertex Shader
	vShader = glCreateShader(GL_VERTEX_SHADER);
	const char* vSource = vertexSource.c_str();
	glShaderSource(vShader, 1, &vSource, NULL);
	glCompileShader(vShader);
	checkCompileErrors(vShader, "VERTEX");

	//fragment Shader
	fShader = glCreateShader(GL_FRAGMENT_SHADER);
	const char* fSource = fragmentSource.c_str();
	glShaderSource(fShader, 1, &fSource, NULL);
	glCompileShader(fShader);
	checkCompileErrors(fShader, "FRAGMENT");

	//geometry Shader

	if(geometrySource != ""){
		gShader = glCreateShader(GL_GEOMETRY_SHADER);
		const char* gSource = geometrySource.c_str();
		glShaderSource(gShader, 1, &gSource, NULL);
		glCompileShader(gShader);
		checkCompileErrors(gShader, "GEOMETRY");
	}

	this->id = glCreateProgram();
	glAttachShader(this->id, vShader);
	glAttachShader(this->id, fShader);
	if(geometrySource != "")
		glAttachShader(this->id, gShader);
	glLinkProgram(this->id);
	checkCompileErrors(this->id, "PROGRAM");

	//deleting shaders
	glDeleteShader(vShader);
	glDeleteShader(fShader);
	if(geometrySource != "")
		glDeleteShader(gShader);

}

int Shader::getUniform(const std::string& name){

	int loc = glGetUniformLocation(this->id, name.c_str());
	if(loc == -1) std::cerr << "ERROR::UNIFORM::" << name << " NOT FOUND" << std::endl;
	return loc;
}

void Shader::setInteger(const std::string& name, GLint value, GLboolean useShader){
	if(useShader)
		this->use();
	glUniform1i(getUniform(name), value);
}

void Shader::setVec(const std::string& name, const std::vector<float>& values, GLboolean useShader){

	if(useShader)
		this->use();
	int loc = getUniform(name);

	switch(values.size()){
		case 1:
			glUniform1f(loc, values[0]);
			break;
		case 2:
			glUniform2f(loc, values[0], values[1]);
			break;
		case 3:
			glUniform3f(loc, values[0], values[1], values[2]);
			break;
		case 4:
			glUniform4f(loc, values[0], values[1], values[2], values[3]);
			break;
		default:
			std::cerr << "ERROR::TOO MANY VALUES FOR SetVec" << std::endl;
			break;
	}
}

void Shader::setVec(const std::string& name, const glm::vec2& values, GLboolean useShader){
	if(useShader)
		this->use();
	this->setVec(name, std::vector<float>{values.x, values.y}, useShader);
}

void Shader::setVec(const std::string& name, const glm::vec3& values, GLboolean useShader ){
	if(useShader)
		this->use();
	this->setVec(name, std::vector<float>{values.x, values.y, values.z}, useShader);
}

void Shader::setVec(const std::string& name, const glm::vec4& values, GLboolean useShader){
	if(useShader)
		this->use();
	this->setVec(name, std::vector<float>{values.x, values.y, values.z, values.w}, useShader);
}

void Shader::setMatrix4(const std::string& name, const glm::mat4 &matrix, GLboolean useShader){
	 if (useShader)
        this->use();
    glUniformMatrix4fv(getUniform(name), 1, GL_FALSE, glm::value_ptr(matrix));
}


void Shader::checkCompileErrors(GLuint object, const std::string& type){

	char infoLog[512];
	GLint success;

	if(type != "PROGRAM"){
		glGetShaderiv(object, GL_COMPILE_STATUS, &success);
		if(!success){
			glGetShaderInfoLog(object, 512, NULL, infoLog);
			std::cerr << "ERROR::SHADER COMPILATION ERROR::" << type << "\n"
			 		  << infoLog << "\n-----------------------------------"
			 		  << std::endl;
		}
	}
	else{
		glGetProgramiv(object, GL_LINK_STATUS, &success);
		if(!success){
			glGetProgramInfoLog(object, 512, NULL, infoLog);
			std::cerr << "ERROR::PROGRAM LINKING ERROR::" << type  << "\n"
						<< infoLog << "\n-------------------------------"
						<< std::endl;
		}
	}

}

Shader& Shader::use(){
	glUseProgram(this->id);
	return *this;	
}