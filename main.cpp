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
	player->setFillColor(sf::Color::Magenta);
	sf::Clock jumpTime; ///Tymczasowe, powinno być w klasie Entity lub inaczej rozwiązane
#ifdef DEBUG
	sf::Clock debugTime;
	sf::Vector2f builderSize{50, 100};
	Type builderType = Type::Ground;
	std::vector<Entity>* builderVector = &currentLevel.grounds;
	sf::RectangleShape builderIndicator;
	builderIndicator.setSize(builderSize);
	builderIndicator.setFillColor(sf::Color{0, 0, 100, 120});
	builderIndicator.setOrigin(builderSize.x / 2, builderSize.y / 2);
#endif //DEBUG
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
			sf::Vector2f mouse_position(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y);
			builderIndicator.setPosition(mouse_position);
			if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				createNewEntity(world, builderSize, mouse_position, *builderVector, builderType);
				if(builderType == Type::Hero)
				{
					player = &currentLevel.heroes[0];
					player->setFillColor(sf::Color::Magenta);
				}
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
				player->setFillColor(sf::Color::Magenta);
				debugTime.restart();
			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::M))
			{
				if(builderType == Type::Hero)
				{
					builderType = Type::Ground;
					builderVector = &currentLevel.grounds;
					builderIndicator.setFillColor(sf::Color{0, 0, 100, 120});
				}
				else
				{
					builderType = Type::Hero;
					builderVector = &currentLevel.heroes;
					builderIndicator.setFillColor(sf::Color{100, 0, 0, 120});
				}
			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::LBracket))
			{
				builderSize.x -= 16;
				builderIndicator.setSize(builderSize);
				builderIndicator.setOrigin(builderSize.x / 2, builderSize.y / 2);
			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::RBracket))
			{
				builderSize.x += 16;
				builderIndicator.setSize(builderSize);
				builderIndicator.setOrigin(builderSize.x / 2, builderSize.y / 2);
			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Comma))
			{
				builderSize.y -= 16;
				builderIndicator.setSize(builderSize);
				builderIndicator.setOrigin(builderSize.x / 2, builderSize.y / 2);
			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Period))
			{
				builderSize.y += 16;
				builderIndicator.setSize(builderSize);
				builderIndicator.setOrigin(builderSize.x / 2, builderSize.y / 2);
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
#ifdef DEBUG
		window.draw(builderIndicator);
#endif
		drawLevel(currentLevel, window);
		window.display();
	}
	///Program ended
	return 0;
}

