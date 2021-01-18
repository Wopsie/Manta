#include "mntpch.h"
#include "RenderCommand.h"
#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Manta
{
	//raw pointer but it lasts for lifetime of all of manta
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;

	
}