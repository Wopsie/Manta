#pragma once


#ifdef MNT_PLATFORM_WINDOWS

extern Manta::MantaApp* Manta::CreateApplication();

int main(int argc, char** argv)
{
	auto app = Manta::CreateApplication();
	app->Run();
	delete app;
}

#endif
