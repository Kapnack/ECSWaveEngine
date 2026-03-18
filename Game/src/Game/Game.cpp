#include "Game.h"

Game::Game(int width, int height) : BaseGame(width, height)
{
	Init(width, height);
}

Game::~Game()
{
	Unload();
}

void Game::Init(const int& width, const int& height)
{

}

void Game::Unload()
{
}
