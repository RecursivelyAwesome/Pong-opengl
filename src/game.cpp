#include "game.h"
#include "ballObject.h"

const glm::vec2 PLAYER_SIZE(100, 20);
const GLfloat PLAYER_VELOCITY(1.0f);
const glm::vec2 INITIAL_BALL_VELOCITY(0.4f, -0.4f);
const GLfloat BALL_RADIUS = 12.5f;

GameObject* player;
BallObject* ball;
ParticleGenerator* particleGenerator;

Game::Game(GLuint width, GLuint height):
	state(GameState::GAME_ACTIVE), keys(), width(width), height(height), spriteRenderer(nullptr), level(0)
{
}

Game::~Game(){
	if(spriteRenderer != nullptr)
		delete spriteRenderer;
	if(player != nullptr)
		delete player;
	if(ball)
		delete ball;
}

void Game::init(){
	ResourceManager::loadShader("./shaders/quadShader.vs", "./shaders/quadShader.fs", "sprite");
	ResourceManager::loadShader("./shaders/particle.vs", "./shaders/particle.fs", "particle");

	glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(this->width), static_cast<GLfloat>(this->height), 0.0f, -1.0f, 1.0f);
	ResourceManager::getShader("sprite").use().setMatrix4("projection", projection);
	ResourceManager::getShader("particle").use().setMatrix4("projection", projection);
	ResourceManager::getShader("sprite").setInteger("image", 0);
	ResourceManager::getShader("particle").setInteger("sprite", 0);

	spriteRenderer = new SpriteRenderer(ResourceManager::getShader("sprite"));

	ResourceManager::loadTexture("./media/images/block.png", GL_FALSE, "block");
	ResourceManager::loadTexture("./media/images/block_solid.png", GL_FALSE, "block_solid");
	ResourceManager::loadTexture("./media/images/background.jpg", GL_FALSE, "background");
	ResourceManager::loadTexture("./media/images/paddle.png", GL_TRUE, "paddle");
	ResourceManager::loadTexture("./media/images/face.png", GL_TRUE, "face");
	ResourceManager::loadTexture("./media/images/particle.png", GL_TRUE, "particle");

	glm::vec2 playerPos = glm::vec2(this->width/2 - PLAYER_SIZE.x/2, this->height - PLAYER_SIZE.y);
	player = new GameObject(playerPos, PLAYER_SIZE, ResourceManager::getTexture("paddle"));

	GameLevel one; one.load("./levels/one.lvl", this->width, this->height* 0.5);
	levels.push_back(one);
	this->level = 0;

	//ball
	glm::vec2 ballPos = playerPos + glm::vec2(PLAYER_SIZE.x/2 - BALL_RADIUS, -BALL_RADIUS*2);
	ball = new BallObject(ballPos, BALL_RADIUS, INITIAL_BALL_VELOCITY, ResourceManager::getTexture("face"));
	//particle generator
	particleGenerator = new ParticleGenerator(ResourceManager::getShader("particle"), ResourceManager::getTexture("particle"), 500);

}

void Game::processInput(GLfloat dt){

	if(state == GameState::GAME_ACTIVE){
		GLfloat velocity = PLAYER_VELOCITY* dt;
		if(this->keys[SDLK_a]){
			if(player->position.x >= 0){
				player->position.x -= velocity;
				if(ball->stuck)
					ball->position.x -= velocity;
			}
		}
		if(this->keys[SDLK_d]){
			if(player->position.x <= this->width - player->size.x){
				player->position.x += velocity;
				if(ball->stuck)
					ball->position.x += velocity;
			}
		}
		if(this->keys[SDLK_SPACE]){
			if(ball->stuck) ball->stuck = false;
		}
	}
}

void Game::updateKeys(SDL_Event& e){
	int keyCode = e.key.keysym.sym;

	if(e.type == SDL_KEYDOWN){
		if(keyCode >= 0 && keyCode < 1024)
			keys[keyCode] = true;
	}

	if(e.type == SDL_KEYUP){
		if(keyCode >= 0 && keyCode < 1024)
			keys[keyCode] = false;
	}
}

void Game::update(GLfloat dt){
	ball->move(dt, this->width);
	doCollisions();
	//dt in milliseconds

	particleGenerator->update(dt, *ball, 1, glm::vec2(ball->radius/2));
}

void Game::render(){
	if(this->state == GameState::GAME_ACTIVE){
		//draw the background
		spriteRenderer->drawSprite(ResourceManager::getTexture("background"), glm::vec2(0.0f), glm::vec2(width, height), 0.0f);
		//draw the level
		this->levels[this->level].draw(*spriteRenderer);
		//draw the particles
		particleGenerator->draw();
		//draw the player
		player->draw(*spriteRenderer);
		//draw the ball
		ball->draw(*spriteRenderer);

		if(ball->position.y >= this->height){
			//out of bound ball
			this->resetPlayer();
			this->resetLevel();
		}
	}
}

void Game::resetLevel(){
	this->levels[this->level].load("./levels/one.lvl", this->width, this->height*0.5f);
}

void Game::resetPlayer(){
	glm::vec2 playerPos = glm::vec2(this->width/2 - PLAYER_SIZE.x/2, this->height - PLAYER_SIZE.y);
	player->position = playerPos;
	ball->stuck = true;
	ball->velocity = INITIAL_BALL_VELOCITY;
	glm::vec2 ballPos = playerPos + glm::vec2(PLAYER_SIZE.x/2 - BALL_RADIUS, -BALL_RADIUS*2);
	ball->position = ballPos;
}

//COLLISION RELATED METHODS
GLboolean Game::checkCollision(GameObject& first, GameObject& second){
	bool collisionX = first.position.x + first.size.x >= second.position.x && second.position.x + second.size.x >= first.position.x;
	bool collisionY = first.position.y + first.size.y  >= second.position.y  && second.position.y + second.size.y >= first.position.y;
	return collisionX && collisionY;
}
Collision Game::checkCollision(BallObject& first, GameObject& second){
	glm::vec2 center(first.position + first.radius);
	glm::vec2 aabb_half_extents(second.size.x/2, second.size.y/2);
	glm::vec2 aabb_center(
		second.position.x + aabb_half_extents.x,
		second.position.y + aabb_half_extents.y
		);
	glm::vec2 difference = center - aabb_center;
	glm::vec2 clamped = glm::clamp(difference, -aabb_half_extents, aabb_half_extents);
	glm::vec2 closest = aabb_center + clamped;
	difference = closest - center;

	if(glm::length(difference) <= first.radius){
		return std::make_tuple(GL_TRUE, vectorDirection(difference), difference);
	}
	else
		return std::make_tuple(GL_FALSE, Direction::UP, glm::vec2(0.0f));
}


void Game::doCollisions(){
	for(GameObject& brick: this->levels[this->level].bricks){
		if(!brick.destroyed){
			Collision collision = checkCollision(*ball, brick);

			if(std::get<0>(collision)){
				if(!brick.isSolid)
					brick.destroyed = true;
				//collision resolution
				Direction dir = std::get<1>(collision);
				glm::vec2 diffVector = std::get<2>(collision);
				if(dir == Direction::LEFT || dir == Direction::RIGHT){
					//horizontal collision
					ball->velocity.x *= -1;
					//relocate
					GLfloat penetration = ball->radius - std::abs(diffVector.x);
					if(dir == Direction::LEFT)
						ball->position.x += penetration;
					else
						ball->position.x -= penetration;
				}
				else{
					ball->velocity.y *= -1;
					GLfloat penetration = ball->radius - std::abs(diffVector.y);
					if(dir == Direction::UP)
						ball->position.y -= penetration;
					else 
						ball->position.y += penetration;
				}
			}
		}
	}
	Collision result = checkCollision(*ball, *player);
	if(!ball->stuck && std::get<0>(result)){
		GLfloat centerBoard = player->position.x + player->size.x/2;
		GLfloat distance = ball->position.x + ball->radius - centerBoard;
		GLfloat percent = distance/(player->size.x/2);

		GLfloat strength = 1.0f;
		glm::vec2 oldVelocity = ball->velocity;
		ball->velocity.x = -INITIAL_BALL_VELOCITY.x* percent* strength;
		ball->velocity.y = -1 * std::abs(ball->velocity.y);
		ball->velocity = glm::normalize(ball->velocity)* glm::length(oldVelocity);
	}


}

Direction Game::vectorDirection(glm::vec2 target){
	glm::vec2 compass[] = {
		glm::vec2(0.0f, 1.0f),
		glm::vec2(0.0f, -1.0f),
		glm::vec2(-1.0f, 0.0f),
		glm::vec2(1.0f, 0.0f)
	};
	GLfloat max =0.0f;
	GLuint bestMatch = -1;
	for(GLuint i=0; i<4; i++){
		GLfloat dot = glm::dot(target, compass[i]);
		if(dot > max){
			max = dot;
			bestMatch = i;
		}
	}
	return (Direction)bestMatch;
}
