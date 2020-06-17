#pragma once


#ifdef MNT_PLATFORM_WINDOWS

extern Manta::MantaApp* Manta::CreateApplication();

int main(int argc, char** argv)
{
	Manta::Log::Init();

	MNT_CORE_WARN("Initialized logger!");
	int a = 5;
	MNT_INFO("Hello log! Var={0}", a);
	
	auto app = Manta::CreateApplication();
	app->Run();
	delete app;
}

#endif
