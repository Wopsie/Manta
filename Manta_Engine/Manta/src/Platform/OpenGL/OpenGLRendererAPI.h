#pragma once
#include "Manta/Renderer/RendererAPI.h"

namespace Manta
{
	class OpenGLRendererAPI : public Manta::RendererAPI
	{
	public:
		virtual void Clear(const glm::vec4& a_Color = { 1.0f, 1.0f, 0.0f, 1.0f }) override;
		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& a_VertexArray) override;

	private:

		
	};
}

