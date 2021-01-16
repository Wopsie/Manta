#include "mntpch.h"
#include "Buffer.h"
#include "Renderer.h"

#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Manta
{
	VertexBuffer* VertexBuffer::Create(float* a_Vertices, uint32_t a_Size)
	{
		//query which API is being used
		switch(Renderer::GetAPI())
		{
		case RenderAPI::NONE:
			MNT_CORE_ASSERT(false, "API not supported; return nullptr");
			return nullptr;
			break;
		case RenderAPI::OPENGL:
			return new OpenGLVertexBuffer(a_Vertices, a_Size);
			break;
		default:
			MNT_CORE_ASSERT(false, "Default; return nullptr");
			return nullptr;
		}

		MNT_CORE_ASSERT(false, "idk wtf render api");

		return nullptr;
	}

	IndexBuffer* IndexBuffer::Create(uint32_t* a_Indices, uint32_t a_Size)
	{
		//query which API is being used
		switch (Renderer::GetAPI())
		{
		case RenderAPI::NONE:
			MNT_CORE_ASSERT(false, "API not supported; return nullptr");
			return nullptr;
			break;
		case RenderAPI::OPENGL:
			return new OpenGLIndexBuffer(a_Indices, a_Size);
			break;
		default:
			MNT_CORE_ASSERT(false, "Default; return nullptr");
			return nullptr;
		}

		MNT_CORE_ASSERT(false, "idk wtf render api");

		return nullptr;
	}
}
