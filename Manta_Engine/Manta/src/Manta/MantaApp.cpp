#include "mntpch.h"
#include "MantaApp.h"

#include "Manta/Log.h"

#include <glad/glad.h>

#include "Input.h"

namespace Manta
{
#define BIND_EVENT_FN(x) std::bind(&MantaApp::x, this, std::placeholders::_1)

	MantaApp* MantaApp::s_Instance = nullptr;

	//temp
	static GLenum ShaderDataTypeToOpenGLType(ShaderDataType a_Type)
	{
		switch (a_Type)
		{
			case ShaderDataType::FLOAT:		return GL_FLOAT;
			case ShaderDataType::FLOAT2:	return GL_FLOAT;
			case ShaderDataType::FLOAT3:	return GL_FLOAT;
			case ShaderDataType::FLOAT4:	return GL_FLOAT;
			case ShaderDataType::MAT3:		return GL_FLOAT;
			case ShaderDataType::MAT4:		return GL_FLOAT;
			case ShaderDataType::INT:		return GL_INT;
			case ShaderDataType::INT2:		return GL_INT;
			case ShaderDataType::INT3:		return GL_INT;
			case ShaderDataType::INT4:		return GL_INT;
			case ShaderDataType::BOOL:		return GL_BOOL;
		}
		MNT_CORE_ASSERT(false, "Shader type conversion failed");
		return 0;
	}
	
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
		
		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 
			 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f
		};

		m_VertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

		{	// go out of scope for cleanliness
			BufferLayout layout = {
				{ ShaderDataType::FLOAT3, "a_Position" },
				{ ShaderDataType::FLOAT4, "a_Color" }
			};
			
			m_VertexBuffer->SetLayout(layout);
		}
		
		uint32_t index = 0;
		const auto& layout = m_VertexBuffer->GetLayout();
		for (const auto element : layout)
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(
				index, 
				element.GetComponentCount(), 
				ShaderDataTypeToOpenGLType(element.m_Type), 
				element.m_Normalized ? GL_TRUE : GL_FALSE, 
				layout.GetStride(),
				(const void*)element.m_Offset
			);
			index++;
			
		}
		

		uint32_t indices[3] = { 0,1,2 };
		m_IndexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		
		std::string vertexShaderSource = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			out vec3 v_Position;
			out vec4 v_Color;
		
			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = vec4(a_Position, 1.0);
			}
		)";

		std::string fragmentShaderSource = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			in vec4 v_Color;
		
			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
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
