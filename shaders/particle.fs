#version 330 core

in vec2 texCoords;
in vec4 particleColor;
out vec4 color;

uniform sampler2D sprite;

void main(){
	color = texture(sprite, texCoords)* particleColor;
	// color = vec4(1.0f, 1.0f, 0.0f, 1.0f);
}