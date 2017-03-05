#ifndef DEBUG_HPP
#define DEBUG_HPP

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include "Entity.hpp"
#include "Level.hpp"

class Debug : public sf::Drawable
{
	static Debug* ms_instance;

public:
	static Debug* Instance();
	static void Release();
	void handleEvents(b2World& world, std::shared_ptr<Entity> player);
	bool isOnCooldown() const;
	void setLevel(Level* level);

private:
	Debug();
	~Debug();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	sf::Clock debugTime;
	sf::Vector2f builderSize{32, 32};
	Type builderType{Type::Ground};
	sf::RectangleShape builderIndicator{builderSize};
	Level* levelPointer;
	sf::Font font;
	sf::Text debugText;
};

#endif // DEBUG_HPP
