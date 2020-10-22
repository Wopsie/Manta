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

#ifdef MNT_ENABLE_ASSERTS
	#define MNT_ASSERT(x, ...) { if(!(x)) {MNT_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define MNT_CORE_ASSERT(x, ...) { if(!(x)) {MNT_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } } 
#else
	#define MNT_ASSERT(x, ...)
	#define MNT_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define MNT_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)