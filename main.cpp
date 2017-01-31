#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <iostream>
#include <vector>
#include "Entity.hpp"
#include "Level.hpp"

#define DEBUG

int main()
{
    sf::RenderWindow window(sf::VideoMode(1600, 900), "Test");
	Level currentLevel;
    window.setFramerateLimit(60);
	b2Vec2 gravity(0.f, 9.8f);
    b2World world(gravity);
	/*createNewEntity(world, {32, 32}, {100, 100}, currentLevel.heroes, Type::Hero);
	createNewEntity(world, {800, 10}, {800, 800}, currentLevel.grounds, Type::Ground);
	createNewEntity(world, {100, 10}, {200, 700}, currentLevel.grounds, Type::Ground);
	createNewEntity(world, {50, 100}, {1000, 700}, currentLevel.grounds, Type::Ground);
	currentLevel.saveToFile("default.gms");*/
	currentLevel.loadFromFile(world, "default.gms");
	Entity* player = &currentLevel.heroes[0];
	sf::Clock jumpTime; ///Tymczasowe, powinno być w klasie Gracza, tak samo jak następne linijki
	int maxJumpNumber = 2, currentJumpNumber = 0;
    while(window.isOpen())
    {
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			player->getBody()->ApplyLinearImpulse( b2Vec2(-0.25f,0), player->getBody()->GetWorldCenter(), true);
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			player->getBody()->ApplyLinearImpulse( b2Vec2(0.25f,0), player->getBody()->GetWorldCenter(), true);
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) && jumpTime.getElapsedTime() > sf::milliseconds(500) && currentJumpNumber > 1)
		{
			currentJumpNumber--;
			jumpTime.restart();
			player->getBody()->ApplyLinearImpulse( b2Vec2(0,-10), player->getBody()->GetWorldCenter(), true);
		}
#ifdef DEBUG
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::C))
		{
			sf::Vector2f position(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y);
			createNewEntity(world, {50, 100}, position, currentLevel.grounds, Type::Ground);
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::V))
		{
			sf::Vector2f position(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y);
			createNewEntity(world, {100, 10}, position, currentLevel.grounds, Type::Ground);
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::B))
		{
			currentLevel.saveToFile("map1.gms"); /// .gms == Gandalf Map System
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::N))
		{
			currentLevel.loadFromFile(world, "map1.gms");
		}
#endif
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            window.close();
		world.Step(1/60.f, 8, 3);
		for(Entity& x : currentLevel.heroes)
		{
			b2Fixture* fixtureIterator = x.getBody()->GetFixtureList();
			for(auto &y : currentLevel.grounds)
			{
				if(b2TestOverlap(fixtureIterator->GetAABB(0), y.getBody()->GetFixtureList()->GetAABB(0))) ///Powinno używać sensorów
				{
					currentJumpNumber = maxJumpNumber;
				}
			}
		}
        window.clear();
        drawLevel(currentLevel, window);
        window.display();
    }
	return 0;
}

