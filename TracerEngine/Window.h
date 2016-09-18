#pragma once
#include <Windows.h>
#include <string>
#include <SDL/SDL.h>
#include <GL/glew.h>
#include "Vertex.h"

namespace TE
{
	enum WindowType 
	{ 
		INVISIBLE = 0x1,
		FULLSCREEN = 0x2, 
		BORDERLESS = 0x4
	};

	class Window
	{
	public:
		Window();
		~Window();

		int create(std::string name, int screenWidth, int screenHeight, unsigned int windowTypeFlags);
		void swapBuffer();
		int getScreenWidth();
		int getScreenHeight();
		void setClearColor(float r, float g, float b, float a);
	private:
		SDL_Window* m_pWindow;
		int m_screenWidth;
		int m_screenHeight;
	};
}