#include "mntpch.h"
#include "VertexArray.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Manta
{
	VertexArray* VertexArray::Create()
	{
		//query which API is being used
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::NONE:
			MNT_CORE_ASSERT(false, "API not supported; return nullptr");
			return nullptr;
			break;
		case RendererAPI::API::OPENGL:
			return new OpenGLVertexArray();
			break;
		default:
			MNT_CORE_ASSERT(false, "Default; return nullptr");
			return nullptr;
		}

		MNT_CORE_ASSERT(false, "idk wtf render api");

		return nullptr;
	}
		
}
