#include "mntpch.h"
#include "RendererAPI.h"

namespace Manta
{
	RendererAPI::API RendererAPI::s_API = RendererAPI::API::OPENGL;
	//RendererAPI::s_API = RendererAPI::API::OPENGL;	//research why does this not work?
}