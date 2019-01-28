#ifndef SHADER_H
#define SHADER_H

#include <iostream>

#include <vector>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader{
public:
	GLuint id;
	Shader(){}

	Shader& use();

	void compile(const std::string& vertexSource, const std::string& fragmentSource, const std::string& geometrySource = "");

    void    setInteger  (const std::string& name, GLint value, GLboolean useShader = false);
    void 	setVec	(const std::string& name, const std::vector<float>& values, GLboolean useShader = false);
    void 	setVec	(const std::string& name, const glm::vec2& values, GLboolean useShader = false);
    void 	setVec	(const std::string& name, const glm::vec3& values, GLboolean useShader = false);
    void 	setVec	(const std::string& name, const glm::vec4& values, GLboolean useShader = false);
    void    setMatrix4  (const std::string& name, const glm::mat4 &matrix, GLboolean useShader = false);

private:
	int getUniform(const std::string& name);
	void checkCompileErrors(GLuint object, const std::string& type);

		
};

#endif