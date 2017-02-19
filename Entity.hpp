#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <iostream>

static const float SCALE = 30.f;

enum class Type
{
	Ground, Hero
};

using Position = sf::Vector2f;
using Size = sf::Vector2f;

class Entity: public sf::RectangleShape
{
	public:
		Entity(b2World&, Size, Position, Type);
		~Entity();
		void setBodyPointer(b2Body*);
		b2Body* getBody() const; 
		void setType(const Type t);
		const Type getType() const; 
		const bool canJump(sf::Clock& clock) const;
		void resetJumpNumber();
		void jump(sf::Clock& clock);
		void moveLeft();
		void moveRight();
	private:
		b2Body* body_ptr = nullptr;
		Type type = Type::Ground;
		int current_jump_number = 0;
		constexpr static int maxJumpNumber{2};
};

#endif // ENTITY_HPP
