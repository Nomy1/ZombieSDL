#pragma once
#include <glm/glm.hpp>
#include <TracerEngine/GLTexture.h>
#include <TracerEngine/SpriteBatch.h>

class ViewObject
{
public:
	ViewObject();
	ViewObject(TE::GLTexture tex, glm::vec2 position, glm::vec2 dim);
	virtual ~ViewObject();

	void init(TE::GLTexture tex, glm::vec2 position, glm::vec2 dim);

	void render(TE::SpriteBatch& spriteBatch);
	glm::vec2 getPosition() const;
	void setPosition(glm::vec2 pos);
protected:
	glm::vec2 m_pos;
	glm::vec2 m_dim;
private:
	TE::GLTexture m_tex;
};

