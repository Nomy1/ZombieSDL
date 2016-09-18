#include "ViewObject.hpp"
#include <TracerEngine\Vertex.h>
#include <GL/glew.h>
#include <iostream>

ViewObject::ViewObject()
{
}

ViewObject::ViewObject(TE::GLTexture tex, glm::vec2 position, glm::vec2 dim)
{
	init(tex, position, dim);
}

ViewObject::~ViewObject()
{
}

void ViewObject::init(TE::GLTexture tex, glm::vec2 position, glm::vec2 dim)
{
	m_pos = position;
	m_dim = dim;
	m_tex = tex;
}

void ViewObject::render(TE::SpriteBatch& spriteBatch)
{
	static TE::ColorRGBA8 color { 255, 255, 255, 255 };
	static glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
	glm::vec4 pos(m_pos.x, m_pos.y, m_dim.x, m_dim.y);
	spriteBatch.draw(m_tex.id, pos, uv, 0.0f, color);
}

glm::vec2 ViewObject::getPosition() const
{
	return m_pos;
}

void ViewObject::setPosition(glm::vec2 pos)
{
	m_pos = pos;
}