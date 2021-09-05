#pragma once

#include "RenderCommand.h"
#include "OrthographicCamera.h"
#include "Shader.h"

namespace Manta
{
	class Renderer
	{
	public:
		static void BeginScene(OrthographicCamera& a_Cam); //take in scene parameters
		static void EndScene();
		static void Submit(const std::shared_ptr<Shader>& a_Shader, const std::shared_ptr<VertexArray>& a_VertexArray, const glm::mat4& a_Transform = glm::mat4(1.0f));	//temp shader argument
		
		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

	private:
		//temporary
		struct SceneData
		{
			glm::mat4 m_ViewProjectionMatrix;
		};

		static SceneData* m_SceneData;
		
	};
}

