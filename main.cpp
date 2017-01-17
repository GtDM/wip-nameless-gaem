#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <iostream>
#include <vector>
#include "Entity.hpp"

void drawVector(std::vector<Entity> entities, sf::RenderWindow& window)
{
	for(Entity& entity : entities)
	{
		entity.setPosition(SCALE * entity.getBody()->GetPosition().x, SCALE * entity.getBody()->GetPosition().y);
		window.draw(entity);
	}
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(1600, 900), "Test");
    window.setFramerateLimit(60);
	b2Vec2 gravity(0.f, 9.8f);
    b2World world(gravity);
	std::vector<Entity> heroes;
	std::vector<Entity> grounds;
	createNewEntity(world, {32, 32}, {100, 100}, heroes, Type::Hero);
	Entity* player = &heroes[0];
	createNewEntity(world, {800, 10}, {800, 800}, grounds, Type::Ground);
	createNewEntity(world, {50, 10}, {195, 700}, grounds, Type::Ground);
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
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            window.close();
		world.Step(1/60.f, 8, 3);
		for(Entity& x : heroes)
		{
			b2Fixture* fixtureIterator = x.getBody()->GetFixtureList();
			for(auto &y : grounds)
			{
				if(b2TestOverlap(fixtureIterator->GetAABB(0), y.getBody()->GetFixtureList()->GetAABB(0))) ///Powinno używać sensorów
				{
					currentJumpNumber = maxJumpNumber;
				}
			}
		}
        window.clear();
        drawVector(heroes, window);
        drawVector(grounds, window);
        window.display();
    }
	return 0;
}

