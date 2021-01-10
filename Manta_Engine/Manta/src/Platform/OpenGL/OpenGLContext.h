#pragma once
#include "Manta/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace Manta
{
	class OpenGLContext : public Manta::GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* windowHandle);
		virtual void Init() override;
		virtual void SwapBuffers() override;

	private:
		GLFWwindow* m_WindowHandle;
		
	};
}

