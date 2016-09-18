
#include <SDL/SDL.h>
#include "Player.hpp"

Player::Player()
{
}

Player::Player(TE::GLTexture tex, glm::vec2 position, glm::vec2 dim, float moveSpeed, float detectRadius)
{
	init(tex, position, dim, moveSpeed, detectRadius);
}

Player::~Player()
{
}

void Player::init(TE::GLTexture tex, glm::vec2 position, glm::vec2 dim, float moveSpeed, float detectRadius)
{
	Humanoid::init(tex, position, dim, moveSpeed, detectRadius);
}

void Player::setInput(TE::InputManager& inputManager)
{
	m_inputManager = &inputManager;
}

void Player::update(const std::vector<std::string>& levelData, Player* player, std::vector<Zombie>& zombies
	)
{
	processInput();
	processCollisions(levelData);
}

void Player::processInput()
{
	if (m_inputManager->isKeyDown(SDLK_a))
	{
		translate(glm::vec2(-1.0f, 0.0f));
	}
	if (m_inputManager->isKeyDown(SDLK_d))
	{
		translate(glm::vec2(1.0f, 0.0f));
	}
	if (m_inputManager->isKeyDown(SDLK_w))
	{
		translate(glm::vec2(0.0f, 1.0f));
	}
	if (m_inputManager->isKeyDown(SDLK_s))
	{
		translate(glm::vec2(0.0f, -1.0f));
	}
}


