#include "Utilities.h"
#include "Cleanup.h"

void logSDLError(std::ostream &os, const std::string &msg)
{
	os << msg << " error: " << SDL_GetError() << std::endl;
}








