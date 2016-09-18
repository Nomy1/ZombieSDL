#include <Windows.h>
#include <iostream>
#include <TracerEngine/Sprite.h>
#include <SDL/SDL.h>

#include "Game.hpp"

int main(int argc, char** argv)
{
	Game game;
	game.run();

	return 0;
}