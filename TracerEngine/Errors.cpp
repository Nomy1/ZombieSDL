#include "Errors.h"

#include <iostream>
#include <cstdlib>
#include <SDL/SDL.h>

namespace TE
{
	void fatalError(std::string errorMsg)
	{
		std::cout << errorMsg << std::endl;
		std::cout << "Enter any key to quit.";
		int input;
		std::cin >> input;
		SDL_Quit();
		exit(-1);
	}
}