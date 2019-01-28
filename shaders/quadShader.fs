#version 330 core

in vec2 texCoord;

out vec4 fragPos;

uniform sampler2D image;
uniform vec3 spriteColor;

void main(){
		
	 fragPos = vec4(spriteColor, 1.0f)* texture(image, texCoord);

}