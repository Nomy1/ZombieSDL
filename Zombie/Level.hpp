#pragma once

#include <vector>
#include <string>
#include <TracerEngine\SpriteBatch.h>

#include "ViewObject.hpp"
#include "Player.hpp"
#include "Zombie.hpp"

const float TILE_WIDTH = 100.0f;
const float TILE_HEIGHT = 100.0f;

class Level
{
public:
	Level(const std::string& filename);
	~Level();

	void render();
	Player* getPlayer();
	std::vector<std::string>& getLevelData();
	std::vector<Zombie>& getZombies();
private:
	std::vector<std::string> m_data;
	std::vector<ViewObject> m_viewObjects;
	std::vector<Zombie> m_zombies;
	Player m_player;
	int m_humanCnt;
	TE::SpriteBatch m_spriteBatch;
};

