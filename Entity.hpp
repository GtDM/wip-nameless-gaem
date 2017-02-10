#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

static const float SCALE = 30.f;

enum class Type
{
	Ground, Hero
};

class Entity: public sf::RectangleShape
{
public:
	Entity(Type t = Type::Ground);
	Entity(b2Body*, Type);
	~Entity() = default;
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
	b2Body* bodyPointer = nullptr;
	Type type = Type::Ground;
	int current_jump_number = 0;

};

void createNewEntity(b2World&, sf::Vector2f, sf::Vector2f, std::vector<Entity>&, Type);

#endif // ENTITY_HPP
