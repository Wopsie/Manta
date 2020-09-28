#pragma once
#include "Core.h"
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"

#include "Window.h"
#include "Manta/LayerStack.h"

namespace Manta
{

	class MANTA_API MantaApp
	{
	public:
		MantaApp();
		virtual ~MantaApp();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);
		
	private:
		bool OnWindowClosed(WindowCloseEvent& e);
		
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack;
	};

	//To be defined in CLIENT
	MantaApp* CreateApplication();
}

