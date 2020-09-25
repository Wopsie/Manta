workspace "Manta_Engine"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- include directories relative to root folder
IncludeDir = {}
IncludeDir["GLFW"] = "Manta/vendor/GLFW/include"

include "Manta/vendor/GLFW"

project "Manta"
	location "Manta"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "mntpch.h"
	pchsource "Manta/src/mntpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}"
	}
	
	links
	{
		"GLFW",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"MNT_PLATFORM_WINDOWS",
			"MNT_BUILD_DLL"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

	filter "configurations:Debug"
		defines "MNT_DEBUG"
		symbols "On"
		
	filter "configurations:Release"
		defines "MNT_RELEASE"
		optimize "On"
		
	filter "configurations:Dist"
		defines "MNT_DIST"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs 
	{
		"Manta/vendor/spdlog/include",
		"Manta/src"
	}

	links
	{
		"Manta"
	}
	
	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"MNT_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "MNT_DEBUG"
		symbols "On"
		
	filter "configurations:Release"
		defines "MNT_RELEASE"
		optimize "On"
		
	filter "configurations:Dist"
		defines "MNT_DIST"
		optimize "On"