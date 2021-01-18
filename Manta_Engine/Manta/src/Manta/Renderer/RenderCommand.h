#pragma once

#include "RendererAPI.h"


namespace Manta
{
	class RenderCommand
	{
	public:
		inline static void Clear(const glm::vec4& a_Color)
		{
			s_RendererAPI->Clear(a_Color);
		}
		
		inline static void DrawIndexed(const std::shared_ptr<VertexArray>& a_VertexArray)
		{
			s_RendererAPI->DrawIndexed(a_VertexArray);
		}
		
	private:
		static RendererAPI* s_RendererAPI;
	};
}