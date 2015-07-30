#include "Console.h"


Console::Console(int width, int height) : COLS(width), ROWS(height), consoleTileSprites(COLS * ROWS)
{
}


Console::~Console()
{
}
