#include "Level.hpp"

Level::Level(b2World& world, std::string n)
{
	std::ifstream in("levels/default.ams");
	if(!in)
	{	
		createNewEntity(world, {32, 32}, {100, 100}, heroes, Type::Hero);
		createNewEntity(world, {800, 10}, {800, 800}, grounds, Type::Ground);
		createNewEntity(world, {100, 10}, {200, 700}, grounds, Type::Ground);
		createNewEntity(world, {50, 100}, {1000, 700}, grounds, Type::Ground);
		saveToFile("levels/default.ams");
	}
	else 
	{
		loadFromStream(world, in);
	}
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
	std::size_t entitiesNumber;
	in >> entitiesNumber;
	///Load name
	for(auto i = 0; i != entitiesNumber; ++i)
	{
		///Load an entity
		char type_c;
		sf::Vector2f position, size;
		in >> type_c >> size.x >> size.y >> position.x >> position.y;
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
	out << (heroes.size() + grounds.size()) << "\n";
	for(const auto &entity : heroes) ///Save every hero
	{
		out << 'h' << " " <<
		entity.getSize().x << " " << entity.getSize().y << " " <<
		entity.getBody()->GetPosition().x  * SCALE << " " << entity.getBody()->GetPosition().y  * SCALE  << "\n";
	}
	for(const auto &entity : grounds) ///Save every ground
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

