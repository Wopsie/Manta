#include "mntpch.h"
#include "MantaApp.h"

#include "Manta/Log.h"

#include <glad/glad.h>

#include "Input.h"

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

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

		//triangle
		glGenVertexArrays(1, &m_VertexArray);
		glBindVertexArray(m_VertexArray);
		
		float vertices[3 * 3] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.0f,  0.5f, 0.0f
		};

		m_VertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

		uint32_t indices[3] = { 0,1,2 };
		m_IndexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		
		std::string vertexShaderSource = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;

			out vec3 v_Position;
		
			void main()
			{
				v_Position = a_Position;
				gl_Position = vec4(a_Position, 1.0);
			}
		)";

		std::string fragmentShaderSource = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;
		
			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
			}
		)";

		//reset is apparently a cool way to set unique pointers
		m_Shader.reset(Shader::Create(vertexShaderSource, fragmentShaderSource));
	}

	MantaApp::~MantaApp()
	{
		m_Shader->Unbind();
		m_VertexBuffer->Unbind();
		m_IndexBuffer->Unbind();
	}

	void MantaApp::Run()
	{
		while (m_Running)
		{

			glClearColor(0.2f, 0.2f, 0.2f, 1);
			glClear(GL_COLOR_BUFFER_BIT);


			m_Shader->Bind();
			glBindVertexArray(m_VertexArray);
			glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);
			
			
			//Update loop
			for (Layer* layer: m_LayerStack)
			{
				layer->OnUpdate();
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

			m_Shader->Unbind();

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
