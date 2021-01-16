#include "mntpch.h"
#include "OpenGLBuffer.h"

#include <glad/glad.h>

namespace Manta
{
	//Vertex Buffer
	OpenGLVertexBuffer::OpenGLVertexBuffer(float* a_Vertices, uint32_t a_Size)
	{
		glCreateBuffers(1, &m_RendererID);
		Bind();
		glBufferData(GL_ARRAY_BUFFER, a_Size, a_Vertices, GL_STATIC_DRAW);

	}

	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		glDeleteBuffers(1, &m_RendererID);
	}

	void OpenGLVertexBuffer::Bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	}

	void OpenGLVertexBuffer::Unbind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	// Index Buffer ////////////

	OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* a_Indices, uint32_t a_Count)
		: m_Count(a_Count)
	{
		glCreateBuffers(1, &m_RendererID);
		Bind();
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, a_Count * sizeof(uint32_t), a_Indices, GL_STATIC_DRAW);

	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		glDeleteBuffers(1, &m_RendererID);
	}

	void OpenGLIndexBuffer::Bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
	}

	void OpenGLIndexBuffer::Unbind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
	
}
