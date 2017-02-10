#include "Debug.hpp"
#include <cstdlib> // NULL 

Debug* Debug::ms_instance = NULL;

Debug::Debug()
{
}

Debug::~Debug()
{
}

Debug* Debug::Instance()
{
	if (ms_instance == nullptr) {
		ms_instance = new Debug();
	}
	return ms_instance;
}

void Debug::Release()
{
	if (ms_instance) {
		delete ms_instance;
	}
	ms_instance = NULL;
}

void Debug::draw(RenderTarget& target, RenderStates states) const
{
	
}

void Debug::handleEvents()
{
	
}
