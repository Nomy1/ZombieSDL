#include "Window.h"
#include "Errors.h"
#include "Vertex.h"

namespace TE
{
	Window::Window()
	{
	}

	Window::~Window()
	{
	}

	int Window::create(std::string name, int screenWidth, int screenHeight, unsigned int windowTypeFlags)
	{
		Uint32 windowFlags = SDL_WINDOW_OPENGL;
		if (windowTypeFlags & INVISIBLE)
		{
			windowFlags |= SDL_WINDOW_HIDDEN;
		}
		if (windowTypeFlags & BORDERLESS)
		{
			windowFlags |= SDL_WINDOW_BORDERLESS;
		}
		if (windowTypeFlags & FULLSCREEN)
		{
			windowFlags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
		}

		m_screenWidth = screenWidth;
		m_screenHeight = screenHeight;

		m_pWindow = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, windowFlags);
		if (m_pWindow == nullptr)
		{
			return -1;
		}

		SDL_GLContext glContext = SDL_GL_CreateContext(m_pWindow);
		if (glContext == nullptr)
		{
			fatalError("Could not create GL Context!");
		}

		GLenum initCode = glewInit();
		if (initCode != GLEW_OK)
		{
			fatalError("Could not init GLEW!");
		}

		std::printf("*** OpenGL Ver. %s ***\n", glGetString(GL_VERSION));

		// Set default background clear color
		glClearColor(0, 0, 0, 1);

		// Set VSYNC (0:off, 1:on)
		SDL_GL_SetSwapInterval(0);

		// Enable alpha blending
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		return 0;
	}

	void Window::setClearColor(float r, float g, float b, float a)
	{
		glClearColor(r, g, b, a);
	}

	void Window::swapBuffer()
	{
		SDL_GL_SwapWindow(m_pWindow);
	}
}