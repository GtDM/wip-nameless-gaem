#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <iostream>
#include <vector>
#include "Entity.hpp"
#include "Level.hpp"

#define DEBUG

void manageCollision(Level& level)
{
	for(auto &x : level.heroes)
	{
		b2Fixture* fixtureIterator = x.getBody()->GetFixtureList();
		for(const auto &y : level.grounds)
		{
			///Powinno używać sensorów
			if(b2TestOverlap(fixtureIterator->GetAABB(0), y.getBody()->GetFixtureList()->GetAABB(0)))
			{
				x.resetJumpNumber();
			}
		}
	}
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(1600, 900), "Test");
	window.setFramerateLimit(60);
	b2Vec2 gravity(0.f, 9.8f);
	b2World world(gravity);
	Level currentLevel(world, "default_level");
	Entity* player = &currentLevel.heroes[0];
	sf::Clock jumpTime, debugTime; ///Tymczasowe, powinno być w klasie Entity lub inaczej rozwiązane
	while(window.isOpen())
	{
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			player->moveLeft();
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			player->moveRight();
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) && jumpTime.getElapsedTime() > sf::milliseconds(500) && player->hasJumpLeft())
		{
			jumpTime.restart();
			player->jump();
		}
#ifdef DEBUG
		if(debugTime.getElapsedTime() > sf::milliseconds(500))
		{
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::C))
			{
				sf::Vector2f position(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y);
				createNewEntity(world, {50, 100}, position, currentLevel.grounds, Type::Ground);
				debugTime.restart();
			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::V))
			{
				sf::Vector2f position(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y);
				createNewEntity(world, {100, 10}, position, currentLevel.grounds, Type::Ground);
				debugTime.restart();
			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::B))
			{
				currentLevel.saveToFile("levels/map1.ams"); /// .ams == Awful Map System
				debugTime.restart();
			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::N))
			{
				currentLevel.loadFromFile(world, "levels/map1.ams");
				player = &currentLevel.heroes[0];
				debugTime.restart();
			}
		}
#endif
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			window.close();
		}
		world.Step(1/60.f, 8, 3);
		manageCollision(currentLevel);
		window.clear();
		drawLevel(currentLevel, window);
		window.display();
	}
	///Program ended
	return 0;
}

