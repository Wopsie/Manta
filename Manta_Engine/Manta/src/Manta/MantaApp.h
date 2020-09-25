#pragma once
#include "Core.h"
#include "Events/Event.h"
#include "Window.h"

namespace Manta
{
	class MANTA_API MantaApp
	{
	public:
		MantaApp();
		virtual ~MantaApp();

		void Run();

	private:
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
	};

	//To be defined in CLIENT
	MantaApp* CreateApplication();
}

