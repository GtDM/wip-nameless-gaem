#include "Level.hpp"

Level::Level(std::string n)
{
	setName(n);
}

Level::Level(b2World& world, std::ifstream& in, std::string n)
{
	loadFromStream(world, in);
	setName(n);
}

Level::Level(b2World& world, std::string path, std::string n)
{
	loadFromFile(world, path);
	setName(n);
}

Level::~Level()
{
}

void Level::loadFromStream(b2World& world, std::ifstream& in)
{
	heroes.clear();
	grounds.clear();
	for(b2Body* next = world.GetBodyList(); next != nullptr;)
	{
		b2Body* entity = next;
		next = next->GetNext();
		world.DestroyBody(entity);
	}
	///Load name
	while(!in.eof())
	{
		///Load an entity
		char type_c;
		float sizeX, sizeY, posX, posY;
		in >> type_c >> sizeX >> sizeY >> posX >> posY;
		sf::Vector2f size{sizeX, sizeY};
		sf::Vector2f position{posX, posY};
		if(type_c == 'h')
		{
			createNewEntity(world, size, position, heroes, Type::Hero);
		}
		if(type_c == 'g')
		{
			createNewEntity(world, size, position, grounds, Type::Ground);
		}
	}
}

void Level::loadFromFile(b2World& world, std::string path)
{
	std::ifstream file;
	file.open(path);
	loadFromStream(world, file);
	file.close();
}

void Level::saveToFile(std::string path)
{
	std::ofstream file(path);
	file.seekp(0);
	saveToStream(file);
	file.close();
}

void Level::saveToStream(std::ofstream& out)
{
	///TODO Encryption and Level Name
	for(auto entity : heroes) ///Save every hero
	{
		out << 'h' << " " <<
		entity.getSize().x << " " << entity.getSize().y << " " <<
		entity.getPosition().x << " " << entity.getPosition().y << "\n";
	}
	for(auto entity : grounds) ///Save every ground
	{
		out << 'g' << " " << 
		entity.getSize().x << " " << entity.getSize().y << " " <<
		entity.getPosition().x << " " << entity.getPosition().y << "\n";
	}
}

void Level::setName(std::string word)
{
	name = word;
}

const std::string Level::getName() const
{
	return name;
}

void drawLevel(Level level, sf::RenderWindow& window)
{
	for(Entity& entity : level.grounds)
	{
		entity.setPosition(SCALE * entity.getBody()->GetPosition().x, SCALE * entity.getBody()->GetPosition().y);
		window.draw(entity);
	}
	for(Entity& entity : level.heroes)
	{
		entity.setPosition(SCALE * entity.getBody()->GetPosition().x, SCALE * entity.getBody()->GetPosition().y);
		window.draw(entity);
	}
}

