#include "Game/Game.h"

int main()
{
	Game* game = new Game(800, 800);

	game->Run();

	delete game;
}