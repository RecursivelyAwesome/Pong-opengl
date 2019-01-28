#include "gameObject.h"


GameObject::GameObject(): position(0.0f), size(1.0f), velocity(0.0f), color(1.0f), rotation(0.0f), sprite(), 
						isSolid(false), destroyed(false){

}

GameObject::GameObject(const glm::vec2& pos, const glm::vec2& size, Texture2D& sprite, const glm::vec3& color,
					const glm::vec2& velocity): position(pos), 
					size(size), color(color), rotation(0.0f), velocity(velocity),sprite(sprite), isSolid(false), destroyed(false){

}


void GameObject::draw(SpriteRenderer& spriteRenderer){
	spriteRenderer.drawSprite(sprite, position, size, rotation, color);
}