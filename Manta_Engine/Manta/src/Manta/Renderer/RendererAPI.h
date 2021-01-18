#pragma once
#include <glm/glm.hpp>

#include "VertexArray.h"

namespace Manta
{
	class RendererAPI
	{
	public:
		enum class API
		{
			NONE = 0,
			OPENGL = 1,
			DIRECTX = 2,
			VULKAN = 3,
		};

		virtual void Clear(const glm::vec4& a_Color = {1.0f, 1.0f, 0.0f, 1.0f}) = 0;
		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& a_VertexArray) = 0;

		inline static API GetAPI() { return s_API; }
	private:
		static API s_API;
		
	};
}

