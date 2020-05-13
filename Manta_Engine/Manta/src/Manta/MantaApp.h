#pragma once
#include "Core.h"

namespace Manta
{
	class MANTA_API MantaApp
	{
	public:
		MantaApp();
		virtual ~MantaApp();

		void Run();
	};

	//To be defined in CLIENT
	MantaApp* CreateApplication();
}

