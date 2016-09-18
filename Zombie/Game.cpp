#include <String>
#include <algorithm>
#include <iostream>
#include <TracerEngine\TracerEngine.h>
#include <TracerEngine\InputManager.h>
#include <TracerEngine\GLTexture.h>
#include <TracerEngine\ResourceManager.h>
#include <TracerEngine\Timing.h>
#include <GL/glew.h>
#include <glm/glm.hpp>

#include "Game.hpp"
#include "ViewObject.hpp"
#include "Player.hpp"

Game::Game() : m_gameState(GameState::PLAY), m_screenWidth(1024), m_screenHeight(768), m_currLevel(0), m_player(nullptr)
{
}

Game::~Game()
{
	for (int i = 0; i < m_levels.size(); i++)
	{
		delete m_levels[i];
	}
}

void Game::run()
{
	initSystems();
	initLevel();

	TE::FPSLimiter fpsLimiter;
	fpsLimiter.init(60.0f);

	while (m_gameState != GameState::EXIT)
	{
		fpsLimiter.frameBegin();
		gameLoop();
		fpsLimiter.frameEnd();
	}
}

void Game::initSystems()
{
	TE::init();

	m_pWindow.create("Zombies!", 1024, 760, 0);
	m_pWindow.setClearColor(0.2f, 0.2f, 0.2f, 1.0f);

	{// init shader
		m_shaderProgram.compileShaders("Shaders/vert_colorShading.txt", "Shaders/frag_colorShading.txt");
		m_shaderProgram.addAttribute("vVertex");
		m_shaderProgram.addAttribute("vColor");
		m_shaderProgram.addAttribute("vTexCoord");
		m_shaderProgram.linkShaders();
	}

	{// init camera
		m_camera.init(m_screenWidth, m_screenHeight);
		const float CAMERA_SCALE = 1.0f / 2.0f;
		m_camera.setScale(CAMERA_SCALE);
	}

	{// init sprite batcher 
		m_spriteBatch.init();
	}
}

void Game::initLevel()
{
	m_levels.push_back(new Level("Levels/level1.txt"));
	m_currLevel = 0;
	m_player = new Player();
	m_player = m_levels[m_currLevel]->getPlayer();
	m_player->setInput(m_inputManager);
	m_zombies = &m_levels[m_currLevel]->getZombies();
}

void Game::gameLoop()
{
	processInput();
	processAI();
	processCamera();
	render();
}

void Game::processInput()
{
	m_inputManager.update();

	while (SDL_PollEvent(&m_inputEvent))
	{
		switch (m_inputEvent.type)
		{
		case SDL_QUIT:
			m_gameState = GameState::EXIT;
			break;
		case SDL_KEYDOWN:
			m_inputManager.pressKey(m_inputEvent.key.keysym.sym);
			break;
		case SDL_KEYUP:
			m_inputManager.releaseKey(m_inputEvent.key.keysym.sym);
			break;
		case SDL_MOUSEBUTTONDOWN:
			m_inputManager.pressKey(m_inputEvent.button.button);
			break;
		case SDL_MOUSEBUTTONUP:
			m_inputManager.releaseKey(m_inputEvent.button.button);
			break;
		case SDL_MOUSEMOTION:
			m_inputManager.setMouseScreenPos(m_inputEvent.motion.x, m_inputEvent.motion.y);
			break;
		}
	}
}

void Game::processAI()
{
	m_player->update(m_levels[m_currLevel]->getLevelData(), m_player, *m_zombies);
}

void Game::processCamera()
{
	m_camera.setPosition(m_player->getPosition());
	m_camera.update();
}

void Game::render()
{
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_shaderProgram.enable();

	// send texture
	glActiveTexture(GL_TEXTURE0);
	GLint texLoc = m_shaderProgram.getUniformLoc("mySampler");
	glUniform1i(texLoc, 0);

	// set camera matrix
	GLint camMatrixLoc = m_shaderProgram.getUniformLoc("cameraMatrix");
	glm::mat4 cameraMatrix = m_camera.getCameraMatrix();
	glUniformMatrix4fv(camMatrixLoc, 1, GL_FALSE, &(cameraMatrix[0][0]));

	m_levels[m_currLevel]->render();
	
	m_spriteBatch.begin();
	
	// render player
	m_player->render(m_spriteBatch);

	// render humans
	for (int i = 0; i < m_humans.size(); i++)
	{
		m_humans[i].render(m_spriteBatch);
	}

	m_spriteBatch.end();
	m_spriteBatch.renderBatch();

	glBindTexture(GL_TEXTURE_2D, 0);

	m_shaderProgram.disable();

	m_pWindow.swapBuffer();
}