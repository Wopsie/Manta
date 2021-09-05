#pragma once
#include "Core.h"
#include "Window.h"
#include "Manta/LayerStack.h"
#include "Manta/Events/Event.h"
#include "Manta/Events/ApplicationEvent.h"

#include "Manta/ImGui/ImGuiLayer.h"

#include "Manta/Core/Timestep.h"

namespace Manta
{

	class MantaApp
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
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;

		float m_PrevFrameTime = 0.0f;
		static MantaApp* s_Instance;
	};

	//To be defined in CLIENT
	MantaApp* CreateApplication();
}

