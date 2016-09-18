#include "InputManager.h"
#include <iostream>

namespace TE
{
	InputManager::InputManager()
	{
	}

	InputManager::~InputManager()
	{
	}

	void InputManager::update()
	{
		for (auto& it : m_isPressedMap)
		{
			m_isPrevPressedMap[it.first] = it.second;
		}
	}

	void InputManager::pressKey(unsigned int keyId)
	{
		m_isPressedMap[keyId] = true;
	}

	void InputManager::releaseKey(unsigned int keyId)
	{
		m_isPressedMap[keyId] = false;
	}

	bool InputManager::isKeyDown(unsigned int keyId) const
	{
		auto iterator = m_isPressedMap.find(keyId);
		if (iterator != m_isPressedMap.end())
		{
			return iterator->second;
		}
		else
		{
			return false;
		}
	}

	bool InputManager::onKeyDown(unsigned int keyId) const
	{
		return isKeyDown(keyId) && !wasKeyDown(keyId);
	}

	bool InputManager::wasKeyDown(unsigned int keyId) const
	{
		auto iterator = m_isPrevPressedMap.find(keyId);
		if (iterator != m_isPrevPressedMap.end())
		{
			return iterator->second;
		}
		else
		{
			return false;
		}
	}

	void InputManager::setMouseScreenPos(float xWndPos, float yWndPos)
	{
		m_mouseScreenPos.x = xWndPos;
		m_mouseScreenPos.y = yWndPos;
	}

	glm::vec2 InputManager::getMouseScreenPos() const { return m_mouseScreenPos; }
}
