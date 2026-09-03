#include "Game.h"

Game::Game(int width, int height) : BaseGame(width, height)
{
	Init(width, height);
}

Game::~Game()
{
	Unload();
}

void Game::Init(int width, int height)
{

}

void Game::Unload()
{
}
