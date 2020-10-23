#include <Manta.h>


class ExampleLayer : public Manta::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
		
	}

	void OnUpdate() override
	{
		//MNT_INFO("ExampleLayer::Update");
		if(Manta::Input::IsKeyPressed(MNT_KEY_TAB))
			MNT_INFO("Tab  key is pressed");
	}

	void OnEvent(Manta::Event& event) override
	{

		if(event.GetEventType() == Manta::EventType::KeyPressed)
		{
			Manta::KeyPressedEvent& e = static_cast<Manta::KeyPressedEvent&>(event);
			MNT_TRACE("{0}", static_cast<char>(e.GetKeyCode()));
		}
	}
};


class Sandbox : public Manta::MantaApp
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
		PushOverlay(new Manta::ImGuiLayer());
	}

	~Sandbox()
	{
		
	}
};

Manta::MantaApp* Manta::CreateApplication()
{
	return new Sandbox();
}
