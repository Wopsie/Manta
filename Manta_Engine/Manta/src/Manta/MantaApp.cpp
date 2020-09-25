#include "mntpch.h"
#include "MantaApp.h"

#include "Manta/Events/ApplicationEvent.h"
#include "Manta/Log.h"

#include <GLFW/glfw3.h>

namespace Manta
{
	MantaApp::MantaApp()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
	}

	MantaApp::~MantaApp()
	{
		
	}

	void MantaApp::Run()
	{
		while (m_Running)
		{
			//glClearColor(1, 0, 1, 1);
			//glClear(GL_COLOR_BUFFER_BIT);
			m_Window->OnUpdate();
		}
	}


}
