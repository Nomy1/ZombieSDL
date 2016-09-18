#include "Humanoid.hpp"
#include "ViewObject.hpp"
#include "Level.hpp"
#include <TracerEngine/GLTexture.h>
#include <algorithm>
#include <glm/glm.hpp>

Humanoid::Humanoid()
{
}

Humanoid::Humanoid(TE::GLTexture tex, glm::vec2 position, glm::vec2 dim, float moveSpeed, float detectRadius)
{
	init(tex, position, dim, moveSpeed, detectRadius);
}

Humanoid::~Humanoid()
{
}

void Humanoid::init(TE::GLTexture tex, glm::vec2 position, glm::vec2 dim, float moveSpeed, float detectRadius)
{
	ViewObject::init(tex, position, dim);
	m_moveSpeed = moveSpeed;
	m_detectRadius = detectRadius;
}

void Humanoid::translate(glm::vec2 dir)
{
	m_pos += (glm::normalize(dir) * m_moveSpeed);
}

void Humanoid::processCollisions(const std::vector<std::string>& levelData)
{
	std::vector<glm::vec2> collideTilePos;
	
	// check four corners
	checkTilePos(levelData, collideTilePos, m_pos.x, m_pos.y);
	checkTilePos(levelData, collideTilePos, m_pos.x + m_dim.x, m_pos.y);
	checkTilePos(levelData, collideTilePos, m_pos.x, m_pos.y + m_dim.y);
	checkTilePos(levelData, collideTilePos, m_pos.x + m_dim.x, m_pos.y + m_dim.y);

	// do collision
	for (int i = 0; i < collideTilePos.size(); i++)
	{
		colliderWithTile(collideTilePos[i]);
	}
}

void Humanoid::checkTilePos(const std::vector<std::string>& levelData, std::vector<glm::vec2>& tilePos, float x, float y)
{
	glm::vec2 cornerPos = glm::ivec2(
		floor(x / (float)TILE_WIDTH),
		floor(y / (float)TILE_HEIGHT));

	// collidable
	if (levelData[cornerPos.y][cornerPos.x] != '.')
	{
		tilePos.push_back(cornerPos * (float)TILE_WIDTH + glm::vec2((float)TILE_WIDTH / 2.0f));
	}
}

void Humanoid::colliderWithTile(glm::vec2 tilePos)
{
	const float TILE_RADIUS = (float)TILE_WIDTH / 2.0f;
	// The minimum distance before a collision occurs
	const float MIN_DISTANCE = TILE_WIDTH + TILE_RADIUS;

	// Center position of the agent
	glm::vec2 centerAgentPos = m_pos + glm::vec2(TILE_WIDTH);
	// Vector from the agent to the tile
	glm::vec2 distVec = centerAgentPos - tilePos;

	// Get the depth of the collision
	float xDepth = MIN_DISTANCE - abs(distVec.x);
	float yDepth = MIN_DISTANCE - abs(distVec.y);

	// If either the depths are > 0, then we collided
	if (xDepth > 0 && yDepth > 0) {

		// Check which collision depth is less
		if (std::max(xDepth, 0.0f) < std::max(yDepth, 0.0f)) {
			// X collsion depth is smaller so we push in X direction
			if (distVec.x < 0) {
				m_pos.x -= xDepth;
			}
			else {
				m_pos.x += xDepth;
			}
		}
		else {
			// Y collsion depth is smaller so we push in X direction
			if (distVec.y < 0) {
				m_pos.y -= yDepth;
			}
			else {
				m_pos.y += yDepth;
			}
		}
	}
}