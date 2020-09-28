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
		MNT_INFO("ExampleLayer::Update");
	}

	void OnEvent(Manta::Event& event) override
	{
		MNT_TRACE("{0}", event);
	}
};


class Sandbox : public Manta::MantaApp
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{
		
	}
};

Manta::MantaApp* Manta::CreateApplication()
{
	return new Sandbox();
}
