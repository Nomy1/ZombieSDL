#include "Camera2D.h"

namespace TE
{
	Camera2D::Camera2D() :
		m_position(0.0f, 0.0f),
		m_cameraMatrix(1.0f),
		m_orthoMatrix(1.0f),
		m_scale(1.0f),
		m_isNeedMatrixUpdate(true),
		m_screenWidth(500),
		m_screenHeight(500)
	{
	}

	Camera2D::~Camera2D()
	{
	}

	void Camera2D::init(int screenWidth, int screenHeight)
	{
		m_screenWidth = screenWidth;
		m_screenHeight = screenHeight;
		m_orthoMatrix = glm::ortho(0.0f, static_cast<float>(m_screenWidth), 0.0f, static_cast<float>(m_screenHeight));
	}

	void Camera2D::update()
	{
		if (m_isNeedMatrixUpdate)
		{
			m_isNeedMatrixUpdate = false;

			// Camera translation
			glm::vec3 translate(-m_position.x + m_screenWidth / 2, -m_position.y + m_screenHeight / 2, 0.0f);
			m_cameraMatrix = glm::translate(m_orthoMatrix, translate);

			// Camera scale
			glm::vec3 scale(m_scale, m_scale, 0.0f);
			m_cameraMatrix = glm::scale(glm::mat4(1.0f), scale) * m_cameraMatrix;
		}
	}

	glm::vec2 Camera2D::convertScreenToWorld(glm::vec2 screenCoord)
	{
		// center to origin
		glm::vec2 worldCoord(screenCoord.x - m_screenWidth / 2, screenCoord.y - m_screenHeight / 2);
		// scale
		worldCoord /= m_scale;
		// translate with regard to camera position
		worldCoord += m_position;
		worldCoord.y *= -1.0f;

		return worldCoord;
	}

	// setters
	void Camera2D::setPosition(const glm::vec2& newPosition) { m_position = newPosition; m_isNeedMatrixUpdate = true; }
	void Camera2D::setScale(float newScale) { m_scale = newScale; m_isNeedMatrixUpdate = true; }

	// getters
	glm::vec2 Camera2D::getPosition() { return m_position; }
	float Camera2D::getScale() { return m_scale; }
	glm::mat4 Camera2D::getCameraMatrix() { return m_cameraMatrix; }
}