#include "Entity.hpp"

Entity::Entity(Type t)
{
	type = t;
}

Entity::Entity(b2Body* ptr, Type t = Type::Ground)
{
	bodyPointer = ptr;
	type = t;
}

Entity::~Entity()
{
}

const Entity& Entity::setBodyPointer(b2Body* ptr)
{
	bodyPointer = ptr;
	return *this;
}

b2Body* Entity::getBody() const
{
	return bodyPointer;
}

const Entity& Entity::setType(const Type t)
{
	type = t;
	return *this;
}
const Type Entity::getType()
{
	return type;
}

void createNewEntity(b2World& world, sf::Vector2f size, sf::Vector2f position, std::vector<Entity>& v, Type t)
{
	Entity entity{t};
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
			entity.setFillColor(sf::Color::Red);
			bodyDef.type = b2_dynamicBody;
			bodyDef.fixedRotation = true;
			fixtureDef.density = 1.f;
			fixtureDef.friction = 0.05f;
			break;
		}
		case Type::Ground:
		{
			entity.setFillColor(sf::Color::Blue);
			bodyDef.type = b2_staticBody;
			fixtureDef.density = 0.f;
			fixtureDef.friction = 0.5f;
			break;
		}
		default:
			break;
	}
	b2Body* body = world.CreateBody(&bodyDef);
	body->CreateFixture(&fixtureDef);
	if(t == Type::Hero)
	{
		shape.SetAsBox(0.3, 0.3, b2Vec2(0,0.3), 0);
		fixtureDef.isSensor = true;
		body->CreateFixture(&fixtureDef);
	}
	entity.setBodyPointer(body);
	entity.setSize(size);
	entity.setOrigin(size.x/2, size.y/2);
	entity.setPosition(position);
	v.push_back(entity);
	

}


    


