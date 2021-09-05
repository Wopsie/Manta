#include "mntpch.h"
#include "MantaApp.h"

#include "Manta/Log.h"
#include "Renderer/Renderer.h"

#include <GLFW/glfw3.h>

namespace Manta
{
#define BIND_EVENT_FN(x) std::bind(&MantaApp::x, this, std::placeholders::_1)

	MantaApp* MantaApp::s_Instance = nullptr;
	
	MantaApp::MantaApp()
		
	{
		MNT_CORE_ASSERT(!s_Instance, "Manta Application already exists");
		s_Instance = this;
		
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));	//research placeholders
		m_Window->SetVSync(false);

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);
	}

	MantaApp::~MantaApp()
	{
	}

	void MantaApp::Run()
	{
		while (m_Running)
		{
			float time = static_cast<float>(glfwGetTime());	//temp
			Timestep timestep = time - m_PrevFrameTime;
			m_PrevFrameTime = time;

			//Update loop
			for (Layer* layer: m_LayerStack)
			{
				layer->OnUpdate(timestep);
				//MNT_INFO("{0}", layer->GetName());
			}

			//Render loop standin
			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
			{
				layer->OnImGuiRender();
			}
			m_ImGuiLayer->End();
			
			m_Window->OnUpdate();
		}
	}

	void MantaApp::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);

		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClosed));
		//MNT_CORE_TRACE("{0}", e);

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
		layer->OnAttach();
	}

	void MantaApp::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}

	bool MantaApp::OnWindowClosed(WindowCloseEvent &e)
	{
		m_Running = false;
		return true;
	}
}
