#define DEBUG

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <iostream>
#include <vector>
#include "Entity.hpp"
#include "Level.hpp"

#ifdef DEBUG ///TODO Somehow cleanup the ifdef mess
#include "Debug.hpp"
#endif

int main()
{
	sf::RenderWindow window(sf::VideoMode(1600, 900), "Test");
	window.setFramerateLimit(60);
	b2World world(b2Vec2{0.f, 9.8f});
	Level currentLevel(world, "default_level");
	Entity* player = &currentLevel.heroes[0];
	player->setFillColor(sf::Color::Magenta);
	sf::Clock jumpTime;
#ifdef DEBUG
	Debug* debug = Debug::Instance();
	debug->setLevel(&currentLevel);
#endif //DEBUG
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
#ifdef DEBUG
		if(!debug->isOnCooldown())
			debug->handleEvents(world, player);
#endif
		world.Step(1/60.f, 8, 3);
		currentLevel.update();
		window.clear();
#ifdef DEBUG
		window.draw(*debug);
#endif
		window.draw(currentLevel);
		window.display();
	}
	///Program ended
#ifdef DEBUG
	Debug::Release();
#endif
	return 0;
}

