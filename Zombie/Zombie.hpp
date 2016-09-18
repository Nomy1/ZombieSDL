#pragma once
#include "Humanoid.hpp"
#include <glm\glm.hpp>
#include <TracerEngine\GLTexture.h>

class Zombie : public Humanoid
{
public:
	Zombie();
	Zombie(TE::GLTexture tex, glm::vec2 pos, glm::vec2 dim, float moveSpeed, float detectRadius);
	virtual ~Zombie();

	void init(TE::GLTexture tex, glm::vec2 position, glm::vec2 dim, float moveSpeed, float detectRadius);

	void update(const std::vector<std::string>& levelData,
		Player* player,
		std::vector<Zombie>& zombies
		);
};

