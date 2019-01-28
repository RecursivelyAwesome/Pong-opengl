#version 330 core

layout(location=0) in vec4 inVertex; //vertex and texture coord

out vec2 texCoord;

uniform mat4 model;
uniform mat4 projection;

void main(){
	
	texCoord = inVertex.zw;
	gl_Position =  projection* model* vec4(inVertex.xy, 0.0f, 1.0f);

}