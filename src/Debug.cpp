#include "Debug.hpp"

Debug* Debug::ms_instance = nullptr;

Debug::Debug()
{
	builderIndicator.setFillColor(sf::Color{0, 0, 100, 120});
	builderIndicator.setOrigin(builderSize.x / 2, builderSize.y / 2);
	font.loadFromFile("/usr/share/fonts/TTF/DejaVuSans.ttf");
	debugText.setFont(font);
	debugText.setString("DEBUG is ON!\n");
}

Debug::~Debug()
{
}

Debug* Debug::Instance()
{
	if(ms_instance == nullptr)
	{
		ms_instance = new Debug();
	}
	return ms_instance;
}

void Debug::Release()
{
	if(ms_instance)
	{
		delete ms_instance;
	}
	ms_instance = nullptr;
}

void Debug::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(builderIndicator, states);
	target.draw(debugText, states);
}

void Debug::handleEvents(b2World& world, std::shared_ptr<Entity> player)
{
	sf::Vector2f mouse_position(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y);
	builderIndicator.setPosition(mouse_position);
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::B))
	{
		levelPointer->saveToFile("levels/map1.ams"); /// .ams == Awful Map System
		debugTime.restart();
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::N))
	{
		levelPointer->loadFromFile(world, "levels/map1.ams");
		player = levelPointer->heroes[0];
		player->setFillColor(sf::Color::Magenta);
		debugTime.restart();
	}
	if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if(builderType == Type::Hero)
		{
			levelPointer->heroes.push_back(std::make_shared<Entity>(world, builderSize, mouse_position, Type::Hero));
			player = levelPointer->heroes[0];
			player->setFillColor(sf::Color::Magenta);
		}
		else
		{
			levelPointer->grounds.push_back(std::make_shared<Entity>(world, builderSize, mouse_position, Type::Ground));
		}
		debugTime.restart();
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::M))
	{
		if(builderType == Type::Hero)
		{
			builderType = Type::Ground;
			builderIndicator.setFillColor(sf::Color{0, 0, 100, 120});
		}
		else
		{
			builderType = Type::Hero;
			builderIndicator.setFillColor(sf::Color{100, 0, 0, 120});
		}
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::LBracket) && builderSize.x > 32)
	{
		builderSize.x -= 32;
		builderIndicator.setSize(builderSize);
		builderIndicator.setOrigin(builderSize.x / 2, builderSize.y / 2);
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::RBracket))
	{
		builderSize.x += 32;
		builderIndicator.setSize(builderSize);
		builderIndicator.setOrigin(builderSize.x / 2, builderSize.y / 2);
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Comma) && builderSize.y > 32)
	{
		builderSize.y -= 32;
		builderIndicator.setSize(builderSize);
		builderIndicator.setOrigin(builderSize.x / 2, builderSize.y / 2);
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Period))
	{
		builderSize.y += 32;
		builderIndicator.setSize(builderSize);
		builderIndicator.setOrigin(builderSize.x / 2, builderSize.y / 2);
	}
}

bool Debug::isOnCooldown() const
{
	return debugTime.getElapsedTime() < sf::milliseconds(500);
}

void Debug::setLevel(Level* level_pointer)
{
	levelPointer = level_pointer;
}
