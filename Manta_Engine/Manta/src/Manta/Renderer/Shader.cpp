#include "mntpch.h"
#include "Shader.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Manta
{
	Shader* Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		//query API
		switch(Renderer::GetAPI())
		{
		case RendererAPI::API::NONE:
			MNT_CORE_ASSERT(false, "No API defined; return nullptr");
			return nullptr;
			break;
		case RendererAPI::API::OPENGL:
			return new OpenGLShader(vertexSrc, fragmentSrc);
			break;
		default:
			MNT_CORE_ASSERT(false, "Default; return nullptr");
			return nullptr;
		}
	}
}
