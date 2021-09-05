#include <Manta.h>
#include <glm/gtc/matrix_transform.hpp>

#include "imgui/imgui.h"



//#include "imgui/imgui.h"

class ExampleLayer : public Manta::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_OrthoCam(-1.6f, 1.6f, -0.9f, 0.9f), m_CamPosition(0.0f)
	{
		//triangle///////////////////////////////////////////////////////
		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f
		};

		m_VertexArray.reset(Manta::VertexArray::Create());

		//Vertex buffer
		std::shared_ptr<Manta::VertexBuffer> triangleVB;
		triangleVB.reset(Manta::VertexBuffer::Create(vertices, sizeof(vertices)));
		Manta::BufferLayout layout = {
			{ Manta::ShaderDataType::FLOAT3, "a_Position" },
			{ Manta::ShaderDataType::FLOAT4, "a_Color" }
		};
		triangleVB->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(triangleVB);

		//Index buffer
		uint32_t indices[3] = { 0,1,2 };
		std::shared_ptr<Manta::IndexBuffer> triangleIB;
		triangleIB.reset(Manta::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(triangleIB);

		//Square///////////////////////////////////////////////////////
		float squareVertices[3 * 4] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f
		};

		m_SquareVertexArray.reset(Manta::VertexArray::Create());

		//Square vertex buffer
		std::shared_ptr<Manta::VertexBuffer> squareVB;
		squareVB.reset(Manta::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));

		squareVB->SetLayout({
			{Manta::ShaderDataType::FLOAT3, "a_Position"}
			});
		m_SquareVertexArray->AddVertexBuffer(squareVB);


		//Square Index buffer
		uint32_t squareIndices[6] = { 0,1,2,2,3,0 };
		std::shared_ptr<Manta::IndexBuffer> squareIB;
		squareIB.reset(Manta::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVertexArray->SetIndexBuffer(squareIB);


		std::string vertexShaderSource = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;
		
			out vec3 v_Position;
			out vec4 v_Color;
		
			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
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
		m_Shader.reset(Manta::Shader::Create(vertexShaderSource, fragmentShaderSource));

		std::string vertexShaderSourceSquare = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;
		
			out vec3 v_Position;
		
			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";

		std::string fragmentShaderSourceSquare = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;
		
			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
			}
		)";

		//reset is apparently a cool way to set unique pointers
		m_SquareShader.reset(Manta::Shader::Create(vertexShaderSourceSquare, fragmentShaderSourceSquare));
	}

	void OnUpdate(Manta::Timestep a_TS) override
	{
		MNT_TRACE("Delta time: {0}s ({1}ms)", a_TS.GetSeconds(), a_TS.GetMilliseconds());

		m_CamPosition = m_OrthoCam.GetPosition();


		//Camera movement input polling
		if (Manta::Input::IsKeyPressed(MNT_KEY_LEFT) || Manta::Input::IsKeyPressed(MNT_KEY_A))
			m_CamPosition.x += m_CamMoveSpeed * a_TS;
		else if (Manta::Input::IsKeyPressed(MNT_KEY_RIGHT) || Manta::Input::IsKeyPressed(MNT_KEY_D))
			m_CamPosition.x -= m_CamMoveSpeed * a_TS;

		if (Manta::Input::IsKeyPressed(MNT_KEY_UP) || Manta::Input::IsKeyPressed(MNT_KEY_W))
			m_CamPosition.y -= m_CamMoveSpeed * a_TS;
		else if (Manta::Input::IsKeyPressed(MNT_KEY_DOWN) || Manta::Input::IsKeyPressed(MNT_KEY_S))
			m_CamPosition.y += m_CamMoveSpeed * a_TS;

		if (Manta::Input::IsKeyPressed(MNT_KEY_E))
			m_CamRotation += m_CamRotationSpeed * a_TS;
		else if (Manta::Input::IsKeyPressed(MNT_KEY_Q))
			m_CamRotation -= m_CamRotationSpeed * a_TS;

		Manta::RenderCommand::Clear({ 0.2f, 0.2f, 0.2f, 1 });

		m_OrthoCam.SetPosition(m_CamPosition);
		m_OrthoCam.SetRotation(m_CamRotation);

		Manta::Renderer::BeginScene(m_OrthoCam);

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		for (int x = 0; x < 20; x++)
		{
			for (int y = 0; y < 20; y++)
			{
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(x * 0.11f, y * 0.11f, 0.f)) * scale;
				Manta::Renderer::Submit(m_SquareShader, m_SquareVertexArray, transform);	//to be overloaded
			}
		}

		Manta::Renderer::Submit(m_Shader, m_VertexArray);	//to be overloaded
		Manta::Renderer::EndScene();

	}

	virtual void OnImGuiRender() override
	{

	}

	void OnEvent(Manta::Event& event) override
	{
	}


private:
	std::shared_ptr<Manta::Shader> m_Shader;
	std::shared_ptr<Manta::VertexArray> m_VertexArray;

	std::shared_ptr<Manta::VertexArray> m_SquareVertexArray;
	std::shared_ptr<Manta::Shader> m_SquareShader;

	Manta::OrthographicCamera m_OrthoCam;

	glm::vec3 m_CamPosition = { 0.f,0.f,0.f };
	float m_CamMoveSpeed = 5.f;
	float m_CamRotation = 0.f;
	float m_CamRotationSpeed = 180.f;
};


class Sandbox : public Manta::MantaApp
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
		//PushOverlay(new Manta::ImGuiLayer());
	}

	~Sandbox()
	{
		
	}
};

Manta::MantaApp* Manta::CreateApplication()
{
	return new Sandbox();
}
