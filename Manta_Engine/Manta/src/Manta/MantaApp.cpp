#include "mntpch.h"
#include "MantaApp.h"

#include "Manta/Log.h"

#include <GLFW/glfw3.h>

namespace Manta
{
#define BIND_EVENT_FN(x) std::bind(&MantaApp::x, this, std::placeholders::_1)
	
	MantaApp::MantaApp()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));	//research placeholders
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

			for (Layer* layer: m_LayerStack)
			{
				layer->OnUpdate();
			}
		}
	}

	void MantaApp::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);

		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClosed));
		MNT_CORE_TRACE("{0}", e);

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
		{
			(*--it)->OnEvent(e);
			if(e.m_Handled)
			{
				break;
			}
		}
	}

	void MantaApp::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
	}

	void MantaApp::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
	}

	bool MantaApp::OnWindowClosed(WindowCloseEvent &e)
	{
		m_Running = false;
		return true;
	}

}
