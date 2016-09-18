#pragma once

#include <vector>
#include <string>
#include <TracerEngine\CircleCollider.hpp>
#include <glm/glm.hpp>

#include "ViewObject.hpp"

class Player;
class Zombie;

class Humanoid : public ViewObject
{
public:
	Humanoid();
	Humanoid(TE::GLTexture tex, glm::vec2 position, glm::vec2 dim, float moveSpeed, float detectRadius);
	virtual ~Humanoid();

	void init(TE::GLTexture tex, glm::vec2 position, glm::vec2 dim, float moveSpeed, float detectRadius);
	void initCollider(float radius);
	
	void translate(glm::vec2 translation);

	// pass level, player, and zombie data for all entities to use
	virtual void update(
		const std::vector<std::string>& levelData,
		Player* player,
		std::vector<Zombie>& zombies
		) = 0;

protected:
	void processCollisions(const std::vector<std::string>& levelData);
	void checkTilePos(const std::vector<std::string>& levelData, std::vector<glm::vec2>& tilePos, float x, float y);
	void colliderWithTile(glm::vec2 tilePos);

	float m_detectRadius;
	float m_moveSpeed;
	glm::vec2 m_moveVector;
};

