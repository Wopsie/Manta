#include <Manta.h>

class Sandbox : public Manta::MantaApp
{
public:
	Sandbox()
	{
		
	}

	~Sandbox()
	{
		
	}
};

Manta::MantaApp* Manta::CreateApplication()
{
	return new Sandbox();
}
