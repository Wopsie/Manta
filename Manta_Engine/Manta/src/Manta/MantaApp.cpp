#include "mntpch.h"
#include "MantaApp.h"

#include "Manta/Events/ApplicationEvent.h"
#include "Manta/Log.h"

namespace Manta
{
	MantaApp::MantaApp()
	{
		
	}

	MantaApp::~MantaApp()
	{
		
	}

	void MantaApp::Run()
	{
		WindowResizeEvent e(1280, 720);
		MNT_TRACE(e);

		while (true);
	}


}
