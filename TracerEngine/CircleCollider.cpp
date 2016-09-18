#include "CircleCollider.hpp"
#include <glm/glm.hpp>

CircleCollider::CircleCollider(glm::vec2 pos, float radius) : pos(pos), radius(radius)
{
}

CircleCollider::~CircleCollider()
{
}

bool CircleCollider::isCollision(const CircleCollider& otherCircle) const
{
	return (glm::distance(otherCircle.pos, pos) < (otherCircle.radius + radius));
}

bool CircleCollider::isCollision(glm::vec2 otherRectPos, glm::vec2 otherRectSize)
{
	return false;
}

glm::vec2 CircleCollider::getDirection(const CircleCollider& otherCircle) const
{
	return glm::normalize(otherCircle.pos - pos);
}