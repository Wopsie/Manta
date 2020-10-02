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

		inline Window& GetWindow() { return *m_Window; }
		inline static MantaApp& Get() { return *s_Instance; }
		
	private:
		bool OnWindowClosed(WindowCloseEvent& e);
		
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack;

		static MantaApp* s_Instance;
	};

	//To be defined in CLIENT
	MantaApp* CreateApplication();
}

