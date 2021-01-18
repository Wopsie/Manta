#include "mntpch.h"
#include "OpenGLRendererAPI.h"

#include <glad/glad.h>

namespace Manta
{
	void OpenGLRendererAPI::Clear(const glm::vec4& a_Color)
	{
		glClearColor(a_Color.r, a_Color.b, a_Color.g, a_Color.a);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLRendererAPI::DrawIndexed(const std::shared_ptr<VertexArray>& a_VertexArray)
	{
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glDrawElements(GL_TRIANGLES, a_VertexArray->GetIndexBuffers()->GetCount(), GL_UNSIGNED_INT, nullptr);
	}
}
