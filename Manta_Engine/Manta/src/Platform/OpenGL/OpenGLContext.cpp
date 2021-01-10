#include "mntpch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Manta
{
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{

		MNT_CORE_ASSERT(m_WindowHandle, "Window handle is null aaa");
		
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		MNT_CORE_ASSERT(status, "Failed to initialize Glad!");

		MNT_CORE_INFO("OpenGL Info:");
		MNT_CORE_INFO("   Vendor: {0}", glGetString(GL_VENDOR));
		MNT_CORE_INFO("   Renderer: {0}", glGetString(GL_RENDERER));
		MNT_CORE_INFO("   Version: {0}", glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}
}
