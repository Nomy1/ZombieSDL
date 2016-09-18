#include "Zombie.hpp"
#include "Humanoid.hpp"

Zombie::Zombie(TE::GLTexture tex, glm::vec2 position, glm::vec2 dim, float moveSpeed, float detectRadius) : Humanoid(tex, position, dim, moveSpeed, detectRadius)
{
}


Zombie::~Zombie()
{
}

void Zombie::update(const std::vector<std::string>& levelData, Player* player, std::vector<Zombie>& zombies)
{

}

void Zombie::init(TE::GLTexture tex, glm::vec2 position, glm::vec2 dim, float moveSpeed, float detectRadius)
{
	Humanoid::init(tex, position, dim, moveSpeed, detectRadius);
}
