#pragma once

namespace Manta
{
	enum class RenderAPI
	{
		NONE = 0,
		OPENGL = 1,
		DIRECTX = 2,
		VULKAN = 3,
	};

	
	class Renderer
	{
	public:
		inline static RenderAPI GetAPI() { return s_RenderAPI; }
	private:
		inline static RenderAPI s_RenderAPI = RenderAPI::OPENGL;
	};
}

