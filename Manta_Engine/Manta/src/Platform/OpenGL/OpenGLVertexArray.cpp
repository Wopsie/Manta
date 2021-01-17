#include "mntpch.h"
#include "OpenGLVertexArray.h"

#include <glad/glad.h>

namespace Manta
{
	//temp
	static GLenum ShaderDataTypeToOpenGLType(ShaderDataType a_Type)
	{
		switch (a_Type)
		{
			case ShaderDataType::FLOAT:		return GL_FLOAT;
			case ShaderDataType::FLOAT2:	return GL_FLOAT;
			case ShaderDataType::FLOAT3:	return GL_FLOAT;
			case ShaderDataType::FLOAT4:	return GL_FLOAT;
			case ShaderDataType::MAT3:		return GL_FLOAT;
			case ShaderDataType::MAT4:		return GL_FLOAT;
			case ShaderDataType::INT:		return GL_INT;
			case ShaderDataType::INT2:		return GL_INT;
			case ShaderDataType::INT3:		return GL_INT;
			case ShaderDataType::INT4:		return GL_INT;
			case ShaderDataType::BOOL:		return GL_BOOL;
		}
		MNT_CORE_ASSERT(false, "Shader type conversion failed");
		return 0;
	}
	
	OpenGLVertexArray::OpenGLVertexArray()
	{
		glCreateVertexArrays(1, &m_RendererID);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &m_RendererID);
	}

	void OpenGLVertexArray::Bind() const
	{
		glBindVertexArray(m_RendererID);
	}

	void OpenGLVertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& a_VertexBuffer)
	{
		MNT_CORE_ASSERT(a_VertexBuffer->GetLayout().GetElements().size(), "vertex buffer layout is null");
		
		//glBindVertexArray(m_RendererID);
		Bind();
		a_VertexBuffer->Bind();

		
		uint32_t index = 0;
		const auto& layout = a_VertexBuffer->GetLayout();
		for (const auto element : layout)
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(
				index,
				element.GetComponentCount(),
				ShaderDataTypeToOpenGLType(element.m_Type),
				element.m_Normalized ? GL_TRUE : GL_FALSE,
				layout.GetStride(),
				(const void*)element.m_Offset
			);
			index++;

		}

		m_VertexBuffers.push_back(a_VertexBuffer);
	}

	void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& a_IndexBuffer)
	{
		//glBindVertexArray(m_RendererID);
		Bind();
		a_IndexBuffer->Bind();

		m_IndexBuffer = a_IndexBuffer;
		
	}
}
