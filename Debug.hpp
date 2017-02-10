#ifndef DEBUG_HPP
#define DEBUG_HPP

#include "Drawable.hpp" // Base class: sf::Drawable

class Debug : public sf::Drawable
{
	static Debug* ms_instance;

public:
	static Debug* Instance();
	static void Release();
	void handleEvents();

private:
	Debug();
	~Debug();
	virtual void draw(RenderTarget& target, RenderStates states) const;
};

#endif // DEBUG_HPP
