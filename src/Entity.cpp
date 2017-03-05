#include "Entity.hpp"

Entity::Entity(b2World& world, Size size, Position position, Type t)
{	
	type = t;
	b2BodyDef bodyDef;
	bodyDef.position = b2Vec2(position.x/SCALE, position.y/SCALE);
	b2PolygonShape shape;
	shape.SetAsBox((size.x/2)/SCALE, (size.y/2)/SCALE);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &shape;
	switch(t)
	{
		case Type::Hero:
		{
			setFillColor(sf::Color::Red);
			bodyDef.type = b2_dynamicBody;
			bodyDef.fixedRotation = true;
			fixtureDef.density = 1.f;
			fixtureDef.friction = 0.75f;
			break;
		}
		case Type::Ground:
		{
			setFillColor(sf::Color::Blue);
			bodyDef.type = b2_staticBody;
			fixtureDef.density = 0.f;
			fixtureDef.friction = 0.5f;
			break;
		}
		default:
			break;
	}
	body_ptr = world.CreateBody(&bodyDef);
	body_ptr->CreateFixture(&fixtureDef);
	if(t == Type::Hero)
	{
		shape.SetAsBox(0.3, 0.3, b2Vec2(0,0.3), 0);
		fixtureDef.isSensor = true;
		body_ptr->CreateFixture(&fixtureDef);
	}
	setSize(size);
	setOrigin(size.x/2, size.y/2);
	setPosition(position);
}

Entity::~Entity()
{
	body_ptr->GetWorld()->DestroyBody(body_ptr);
}

void Entity::setBodyPointer(b2Body* ptr)
{
	body_ptr = ptr;
}

b2Body* Entity::getBody() const
{
	return body_ptr;
}

void Entity::setType(const Type t)
{
	type = t;
}

const Type Entity::getType() const
{
	return type;
}

const bool Entity::canJump(sf::Clock& jumpTime) const
{
	return current_jump_number > 1 && jumpTime.getElapsedTime() > sf::milliseconds(500);
}

void Entity::resetJumpNumber()
{
	current_jump_number = maxJumpNumber;
}

void Entity::jump(sf::Clock& jumpTime)
{
	body_ptr->ApplyLinearImpulse( b2Vec2(0,-10), body_ptr->GetWorldCenter(), true);
	current_jump_number--;
	jumpTime.restart();
}

void Entity::moveLeft()
{
	body_ptr->ApplyLinearImpulse( b2Vec2(-0.25f,0), body_ptr->GetWorldCenter(), true);
}

void Entity::moveRight()
{
	body_ptr->ApplyLinearImpulse( b2Vec2(0.25f,0), body_ptr->GetWorldCenter(), true);
}



    


