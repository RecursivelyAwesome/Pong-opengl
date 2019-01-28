#version 330 core
layout(location=0) in vec4 vertex;

out vec2 texCoords;
out vec4 particleColor;

uniform mat4 projection;
uniform vec2 offset;
uniform vec4 color;

void main(){
	float scale = 10.0f;
	texCoords = vertex.zw;
	particleColor = color;
	gl_Position = projection* vec4((vertex.xy* scale) + offset, 0.0f, 1.0f);
}