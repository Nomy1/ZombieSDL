#pragma once
#include <GL/glew.h>
#include "GLTexture.h"
#include <string>

namespace TE
{
	class Sprite
	{
	public:
		Sprite();
		~Sprite();
		void init(std::string texturePath, float xPos, float yPos, float width, float height);
		void render();

	private:
		float m_xPos, m_yPos;
		float m_width, m_height;
		GLuint m_vertBuffObjId;
		GLTexture m_texture;
	};
}
