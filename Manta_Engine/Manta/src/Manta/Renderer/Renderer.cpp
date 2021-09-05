#include "mntpch.h"
#include "Renderer.h"

namespace Manta
{
	Renderer::SceneData* Renderer::m_SceneData = new Renderer::SceneData;
	
	
	void Renderer::BeginScene(OrthographicCamera& a_Cam)
	{
		m_SceneData->m_ViewProjectionMatrix = a_Cam.GetViewProjectionMatrix();
	}

	void Renderer::EndScene()
	{
	}

	void Renderer::Submit(const std::shared_ptr<Shader>& a_Shader, const std::shared_ptr<VertexArray>& a_VertexArray, const glm::mat4& a_Transform)
	{
		//would do instancing/batching here
		a_Shader->Bind();
		a_Shader->UploadUniformMat4("u_ViewProjection", m_SceneData->m_ViewProjectionMatrix);
		a_Shader->UploadUniformMat4("u_Transform", a_Transform);
		a_VertexArray->Bind();
		RenderCommand::DrawIndexed(a_VertexArray);
	}
}
