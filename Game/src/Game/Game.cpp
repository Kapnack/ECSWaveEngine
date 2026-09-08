#include "Game.h"
#include <Engine/Engine.h>

Game::Game(int width, int height) : Engine(width, height)
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
 