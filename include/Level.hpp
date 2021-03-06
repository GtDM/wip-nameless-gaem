#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <vector>
#include "Entity.hpp"
#include <fstream>

class Level: public sf::Drawable
{
public:
	Level(b2World& world, std::string n); ///TODO simplify Level's constructor
	Level(b2World& world, std::ifstream& in, std::string n);
	Level(b2World& world, std::string path, std::string n);
	~Level();
	void loadFromStream(b2World&, std::ifstream& in);
	void loadFromFile(b2World&, std::string path);
	void saveToStream(std::ofstream& out);
	void saveToFile(std::string path);
	void setName(std::string);
	const std::string getName() const;
	void update();
	std::vector<std::shared_ptr<Entity>> heroes;
	std::vector<std::shared_ptr<Entity>> grounds;
private:
	std::string name;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void manageCollision();
};

#endif // LEVEL_HPP
