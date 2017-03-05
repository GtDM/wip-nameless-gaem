#include "Level.hpp"

Level::Level(b2World& world, std::string n)
{
	if(std::ifstream in("levels/default.ams"); !in)
	{	
		heroes.emplace_back(std::make_shared<Entity>(world, Size{32, 32}, Position{748.782, 778.55}, Type::Hero));
		heroes.emplace_back(std::make_shared<Entity>(world, Size{50, 68}, Position{1237, 440.55}, Type::Hero));
		grounds.emplace_back(std::make_shared<Entity>(world, Size{800, 10}, Position{800, 800}, Type::Ground));
		grounds.emplace_back(std::make_shared<Entity>(world, Size{18, 100}, Position{546, 690}, Type::Ground));
		grounds.emplace_back(std::make_shared<Entity>(world, Size{18, 20}, Position{551, 593}, Type::Ground));
		grounds.emplace_back(std::make_shared<Entity>(world, Size{14, 284}, Position{1027, 498}, Type::Ground));
		grounds.emplace_back(std::make_shared<Entity>(world, Size{306, 16}, Position{1158, 481}, Type::Ground));
		grounds.emplace_back(std::make_shared<Entity>(world, Size{178, 16}, Position{1277, 688}, Type::Ground));
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
	heroes.clear();
	grounds.clear();
}

void Level::loadFromStream(b2World& world, std::ifstream& in)
{
	heroes.clear();
	grounds.clear();
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
			heroes.emplace_back(std::make_shared<Entity>(world, size, position, Type::Hero));
		}
		if(type_c == 'g')
		{
			grounds.emplace_back(std::make_shared<Entity>(world, size, position, Type::Ground));
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
		entity->getSize().x << " " << entity->getSize().y << " " <<
		entity->getBody()->GetPosition().x  * SCALE << " " << entity->getBody()->GetPosition().y  * SCALE  << "\n";
	}
	for(const auto &entity : grounds) ///Save every ground
	{
		out << 'g' << " " << 
		entity->getSize().x << " " << entity->getSize().y << " " <<
		entity->getPosition().x << " " << entity->getPosition().y << "\n";
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

void Level::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for(const auto& entity : grounds)
	{
		target.draw(*entity, states);
	}
	for(const auto& entity : heroes)
	{
		target.draw(*entity, states);
	}
}

void Level::update()
{
	for(auto& entity : grounds)
		entity->setPosition(SCALE * entity->getBody()->GetPosition().x, SCALE * entity->getBody()->GetPosition().y);
	for(auto& entity : heroes)
		entity->setPosition(SCALE * entity->getBody()->GetPosition().x, SCALE * entity->getBody()->GetPosition().y);
	manageCollision();
}

void Level::manageCollision()
{
	for(auto &x : heroes)
	{
		b2Fixture* fixtureIterator = x->getBody()->GetFixtureList();
		for(const auto &y : grounds)
		{
			if(b2TestOverlap(fixtureIterator->GetAABB(0), y->getBody()->GetFixtureList()->GetAABB(0))) ///TODO sensors
			{
				x->resetJumpNumber();
			}
		}
	}
}
