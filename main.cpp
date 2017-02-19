#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <iostream>
#include <vector>
#include "Entity.hpp"
#include "Level.hpp"
#include "Debug.hpp"

constexpr bool DEBUG{true};

int main()
{
	sf::RenderWindow window(sf::VideoMode(1600, 900), "Test");
	window.setFramerateLimit(60);
	b2World world(b2Vec2{0.f, 9.8f});
	Level currentLevel(world, "default_level");
	std::shared_ptr<Entity> player = currentLevel.heroes[0];
	player->setFillColor(sf::Color::Magenta);
	sf::Clock jumpTime;
	if constexpr(DEBUG)
		Debug::Instance()->setLevel(&currentLevel);
	while(window.isOpen())
	{
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			player->moveLeft();
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			player->moveRight();
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) && player->canJump(jumpTime)) ///TODO One Chrono Class to rule time
			player->jump(jumpTime);
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			window.close();
		if constexpr(DEBUG)
		{
			player = nullptr;
			if(!Debug::Instance()->isOnCooldown())
				Debug::Instance()->handleEvents(world, player);
			player = currentLevel.heroes[0];
		}
		world.Step(1/60.f, 8, 3);
		currentLevel.update();
		window.clear();
		if constexpr(DEBUG)
			window.draw(*Debug::Instance());
		window.draw(currentLevel);
		window.display();
	}
	if constexpr(DEBUG)
		Debug::Release();
	return 0;
}

