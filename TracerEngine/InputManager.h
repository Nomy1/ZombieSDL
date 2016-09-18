#pragma once
#include <unordered_map>
#include <glm/glm.hpp>

namespace TE
{
	class InputManager
	{
	public:
		InputManager();
		~InputManager();

		void update();

		void pressKey(unsigned int keyId);
		void releaseKey(unsigned int keyId);
		bool isKeyDown(unsigned int keyId) const;	// key is held down
		bool onKeyDown(unsigned int keyId) const;	// key has just been pressed down
		void setMouseScreenPos(float xWndPos, float yWndPos);
		glm::vec2 getMouseScreenPos() const;
	private:
		bool wasKeyDown(unsigned int keyId) const;
		std::unordered_map<unsigned int, bool> m_isPressedMap;
		std::unordered_map<unsigned int, bool> m_isPrevPressedMap;
		glm::vec2 m_mouseScreenPos;
	};
}

