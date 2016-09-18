#pragma once
#include <glm/glm.hpp>

class CircleCollider
{
public:
	CircleCollider(glm::vec2 pos, float radius);
	~CircleCollider();

	bool isCollision(const CircleCollider& otherCircle) const;
	bool isCollision(glm::vec2 otherRectPos, glm::vec2 otherRectSize);
	glm::vec2 getDirection(const CircleCollider& otherCircle) const;

	glm::vec2 pos;
	float radius;
private:

};

