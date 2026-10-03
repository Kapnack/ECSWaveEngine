#pragma once

#include "Export.h"
#include "ServiceProvider/Service.h"

namespace WaveEngine
{
	class WaveMaterialBehaviourFactory : public Service
	{

	public:

		WaveMaterialBehaviourFactory();
		~WaveMaterialBehaviourFactory();

		void CreateMaterialBehaviour(unsigned int materialID);
	};
}