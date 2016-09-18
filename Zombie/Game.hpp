#pragma once
#include <TracerEngine\Window.h>
#include <TracerEngine\Camera2D.h>
#include <TracerEngine\Errors.h>
#include <TracerEngine\GlslProgram.h>
#include <TracerEngine\InputManager.h>
#include <TracerEngine\ResourceManager.h>
#include <TracerEngine\Vertex.h>
#include <TracerEngine\SpriteBatch.h>
#include <SDL/SDL.h>
#include <vector>

#include "Player.hpp"
#include "Humanoid.hpp"
#include "Zombie.hpp"
#include "Level.hpp"

enum class GameState { PLAY, EXIT };

class Game
{
public:
	Game();
	~Game();

	void run();
private:
	void initSystems();
	void initLevel();
	void gameLoop();
	void processInput();
	void processCommands();
	void processAI();
	void processCamera();
	void render();

	int m_screenWidth;
	int m_screenHeight;
	
	GameState m_gameState;
	TE::Window m_pWindow;
	TE::GlslProgram m_shaderProgram;
	TE::SpriteBatch m_spriteBatch;
	TE::InputManager m_inputManager;
	SDL_Event m_inputEvent;
	TE::Camera2D m_camera;

	// entities
	std::vector<Zombie>* m_zombies;
	std::vector<Humanoid> m_humans;
	Player* m_player;

	// level related
	int m_currLevel;
	std::vector<Level*> m_levels;
};

