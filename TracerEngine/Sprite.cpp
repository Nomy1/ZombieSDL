#include "Sprite.h"
#include "Vertex.h"
#include "GLTexture.h"
#include "ResourceManager.h"
#include <GL/glew.h>
#include <stddef.h>

namespace TE
{
	Sprite::Sprite()
	{
		m_vertBuffObjId = 0;
	}

	Sprite::~Sprite()
	{
		if (m_vertBuffObjId != 0)
		{
			glDeleteBuffers(1, &m_vertBuffObjId);
		}
	}

	void Sprite::init(std::string texturePath, float xPos, float yPos, float width, float height)
	{
		m_xPos = xPos;
		m_yPos = yPos;
		m_width = width;
		m_height = m_height;

		m_texture = ResourceManager::getTexture(texturePath);

		if (m_vertBuffObjId == 0)
		{
			glGenBuffers(1, &m_vertBuffObjId);
		}

		Vertex vertexData[6];

		vertexData[0].setPos(xPos + width, yPos + height);
		vertexData[0].setUV(1.0f, 1.0f);

		vertexData[1].setPos(xPos, yPos + height);
		vertexData[1].setUV(0.0f, 1.0f);

		vertexData[2].setPos(xPos, yPos);
		vertexData[2].setUV(0.0f, 0.0f);

		vertexData[3].setPos(xPos, yPos);
		vertexData[3].setUV(0.0f, 0.0f);

		vertexData[4].setPos(xPos + width, yPos);
		vertexData[4].setUV(1.0f, 0.0f);

		vertexData[5].setPos(xPos + width, yPos + height);
		vertexData[5].setUV(1.0f, 1.0f);

		vertexData[1].setColor(255, 0, 0, 255);
		vertexData[5].setColor(0, 255, 0, 255);

		glBindBuffer(GL_ARRAY_BUFFER, m_vertBuffObjId);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void Sprite::render()
	{
		glBindTexture(GL_TEXTURE_2D, m_texture.id);

		glBindBuffer(GL_ARRAY_BUFFER, m_vertBuffObjId);
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);

		// setup attribute pointers
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, pos));
		glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));

		glDrawArrays(GL_TRIANGLES, 0, 6);

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}