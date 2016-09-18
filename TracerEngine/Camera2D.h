#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace TE
{
	class Camera2D
	{
	public:
		Camera2D();
		~Camera2D();

		void init(int screenWidth, int screenHeight);
		void update();

		glm::vec2 convertScreenToWorld(glm::vec2 screenCoord);

		// setters
		void setPosition(const glm::vec2& newPosition);
		void setScale(float newScale);

		// getters
		glm::vec2 getPosition();
		float getScale();
		glm::mat4 getCameraMatrix();

	private:
		bool m_isNeedMatrixUpdate;
		int m_screenWidth;
		int m_screenHeight;
		glm::vec2 m_position;
		glm::mat4 m_orthoMatrix;
		glm::mat4 m_cameraMatrix;
		float m_scale;
	};
}
