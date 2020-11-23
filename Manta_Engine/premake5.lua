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
IncludeDir["glm"] = "Manta/vendor/glm"

include "Manta/vendor/GLFW"
include "Manta/vendor/Glad"
include "Manta/vendor/imgui"

project "Manta"
	location "Manta"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "mntpch.h"
	pchsource "Manta/src/mntpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl"
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}"
	}
	
	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"MNT_PLATFORM_WINDOWS",
			"MNT_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

	filter "configurations:Debug"
		defines "MNT_DEBUG"
		runtime "Debug"
		symbols "on"
		
	filter "configurations:Release"
		defines "MNT_RELEASE"
		runtime "Release"
		optimize "on"
		
	filter "configurations:Dist"
		defines "MNT_DIST"
		runtime "Release"
		optimize "on"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

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
		"Manta/src",
		"Manta/vendor",
		"%{IncludeDir.glm}"
	}

	links
	{
		"Manta"
	}
	
	filter "system:windows"
		systemversion "latest"

		defines
		{
			"MNT_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "MNT_DEBUG"
		runtime "Debug"
		symbols "on"
		
	filter "configurations:Release"
		defines "MNT_RELEASE"
		runtime "Release"
		optimize "on"
		
	filter "configurations:Dist"
		defines "MNT_DIST"
		runtime "Release"
		optimize "on"