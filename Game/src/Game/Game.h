#pragma once

#include "Engine/Engine.h"

using namespace WaveEngine;

class Game : public Engine
{
private:

protected:

	void Init(int width, int height) override;
	void Unload() override;

public:

	Game(int width, int height);
	~Game();
};

