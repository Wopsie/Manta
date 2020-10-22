workspace "Manta_Engine"
	architecture "x64"
	startproject "Sandbox"
	
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
IncludeDir["Glad"] = "Manta/vendor/Glad/include"
IncludeDir["ImGui"] = "Manta/vendor/imgui"

include "Manta/vendor/GLFW"
include "Manta/vendor/Glad"
include "Manta/vendor/imgui"

project "Manta"
	location "Manta"
	kind "SharedLib"
	language "C++"
	staticruntime "off"

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
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}"
	}
	
	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"MNT_PLATFORM_WINDOWS",
			"MNT_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Sandbox/\"")
		}

	filter "configurations:Debug"
		defines "MNT_DEBUG"
		runtime "Debug"
		symbols "On"
		
	filter "configurations:Release"
		defines "MNT_RELEASE"
		runtime "Release"
		optimize "On"
		
	filter "configurations:Dist"
		defines "MNT_DIST"
		runtime "Release"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	staticruntime "off"

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
		systemversion "latest"

		defines
		{
			"MNT_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "MNT_DEBUG"
		runtime "Debug"
		symbols "On"
		
	filter "configurations:Release"
		defines "MNT_RELEASE"
		runtime "Release"
		optimize "On"
		
	filter "configurations:Dist"
		defines "MNT_DIST"
		runtime "Release"
		optimize "On"