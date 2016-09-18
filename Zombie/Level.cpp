#include <fstream>
#include <iostream>
#include <TracerEngine\Errors.h>
#include <TracerEngine\ResourceManager.h>

#include "Player.hpp"
#include "Level.hpp"

Level::Level(const std::string& filename) : m_player()
{
	std::ifstream file;
	file.open(filename);
	if (file.fail())
	{
		TE::fatalError("Failed to open " + filename);
	}

	// human count in level
	std::string tmp;
	file >> tmp >> m_humanCnt;

	// read in file
	while (std::getline(file, tmp))
	{
		m_data.push_back(tmp);
	}

	m_spriteBatch.init();
	m_spriteBatch.begin();

	static glm::vec2 dim(TILE_WIDTH, TILE_HEIGHT);

	// parse file
	for (int y = 0; y < m_data.size(); ++y)
	{
		for (int x = 0; x < m_data[y].size(); ++x)
		{
			glm::vec2 pos(x*TILE_WIDTH, y*TILE_HEIGHT);

			char tile = m_data[y][x];
			switch (tile)
			{
			case '.': 
				continue;

			// brick tile
			case 'B':
			case 'R':
			{
				TE::GLTexture tex = TE::ResourceManager::getTexture("Textures/red_bricks.png");
				ViewObject obj(tex, pos, dim);
				m_viewObjects.push_back(obj);
				obj.render(m_spriteBatch);
			} break;

			// glass tile
			case 'G':
			{
				TE::GLTexture tex = TE::ResourceManager::getTexture("Textures/glass.png");
				ViewObject obj(tex, pos, dim);
				m_viewObjects.push_back(obj);
				obj.render(m_spriteBatch);
			} break;

			// light bricks
			case 'L':
			{
				TE::GLTexture tex = TE::ResourceManager::getTexture("Textures/light_bricks.png");
				ViewObject obj(tex, pos, dim);
				m_viewObjects.push_back(obj);
				obj.render(m_spriteBatch);
			} break;

			// player
			case '@':
			{
				TE::GLTexture tex = TE::ResourceManager::getTexture("Textures/p1_stand.png");
				m_player.init(tex, pos, dim, 5.0f, 1.0f);
				m_data[y][x] = '.'; // return humanoid place to an empty space
			} break;

			// zombie
			case 'Z':
			{
				TE::GLTexture tex = TE::ResourceManager::getTexture("Textures/p2_duck.png");
				Zombie z(tex, pos, dim, 1.0f, 1.0f);
				m_zombies.push_back(z);
				z.render(m_spriteBatch);
				m_data[y][x] = '.'; // return humanoid place to an empty space
			} break;

			// none
			default:
				TE::fatalError("Unexpected character " + tile);
				break;
			}
		}
	}
	m_spriteBatch.end();
}

Level::~Level()
{
}

std::vector<std::string>& Level::getLevelData()
{
	return m_data;
}

Player* Level::getPlayer()
{
	return &m_player;
}

std::vector<Zombie>& Level::getZombies()
{
	return m_zombies;
}

void Level::render()
{
	m_spriteBatch.renderBatch();
}