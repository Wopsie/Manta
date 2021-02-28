#pragma once
#include "Core.h"
#include "Window.h"
#include "Manta/LayerStack.h"
#include "Manta/Events/Event.h"
#include "Manta/Events/ApplicationEvent.h"

#include "Manta/ImGui/ImGuiLayer.h"
#include "Renderer/Buffer.h"
#include "Renderer/VertexArray.h"

//temp
#include "Manta/Renderer/Shader.h"
#include "Renderer/OrthographicCamera.h"


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
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;

		//unsigned int m_VertexArray;
		std::shared_ptr<Shader> m_Shader;
		std::shared_ptr<VertexArray> m_VertexArray;

		std::shared_ptr<VertexArray> m_SquareVertexArray;
		std::shared_ptr<Shader> m_SquareShader;

		OrthographicCamera m_OrthoCam;
		
		static MantaApp* s_Instance;
	};

	//To be defined in CLIENT
	MantaApp* CreateApplication();
}

