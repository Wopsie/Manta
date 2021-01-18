#include "mntpch.h"
#include "Renderer.h"

namespace Manta
{
	void Renderer::BeginScene()
	{
	}

	void Renderer::EndScene()
	{
	}

	void Renderer::Submit(const std::shared_ptr<VertexArray>& a_VertexArray)
	{
		a_VertexArray->Bind();
		RenderCommand::DrawIndexed(a_VertexArray);
	}
}
