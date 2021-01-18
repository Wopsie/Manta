#pragma once

#include "RenderCommand.h"

namespace Manta
{
	
	class Renderer
	{
	public:
		static void BeginScene(); //take in scene parameters
		static void EndScene();
		static void Submit(const std::shared_ptr<VertexArray>& a_VertexArray);
		
		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	};
}

