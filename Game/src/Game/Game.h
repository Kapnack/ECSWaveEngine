#pragma once

#include "BaseGame/BaseGame.h"

using namespace WaveEngine;

class Game : public WaveEngine::BaseGame
{
private:

protected:

	void Init(const int& width, const int& height) override;
	void Unload() override;

public:

	Game(int width, int height);
	~Game();
};

