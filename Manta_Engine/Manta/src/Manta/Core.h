#pragma once

#ifdef MNT_PLATFORM_WINDOWS
	#ifdef MNT_BUILD_DLL
		#define MANTA_API __declspec(dllexport)
	#else
		#define MANTA_API __declspec(dllimport)
	#endif
#else
	#error Manta only supports windows!
#endif