#pragma once

#include <string>

#include "EventSystem/Event.h"

using namespace std;

namespace WaveEngine
{
	struct ObjectChangeName : public Event
	{
		unsigned int entityID = 0;
		string newName = "";

		ObjectChangeName();

		ObjectChangeName(unsigned int entityID, string newName);

		void Reset() override;
	};
}