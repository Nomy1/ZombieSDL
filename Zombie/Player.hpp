#pragma once

#include <TracerEngine\InputManager.h>

#include "Zombie.hpp"
#include "Player.hpp"

class Player : public Humanoid
{
public:
	Player();
	Player(TE::GLTexture tex, glm::vec2 position, glm::vec2 dim, float moveSpeed, float detectRadius);
	~Player();

	void init(TE::GLTexture tex, glm::vec2 position, glm::vec2 dim, float moveSpeed, float detectRadius);
	
	// pass level, player, and zombie data for all entities to use
	void update(const std::vector<std::string>& levelData,
		Player* player,
		std::vector<Zombie>& zombies
		);

	void setInput(TE::InputManager& inputManager);
private:
	void processInput();
	TE::InputManager* m_inputManager;
};

