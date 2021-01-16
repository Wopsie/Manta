#pragma once
#include "Manta/Renderer/Buffer.h"

namespace Manta
{
	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(float* a_Vertices, uint32_t a_Size);
		virtual ~OpenGLVertexBuffer();

		virtual void Bind() const override;
		virtual void Unbind() const override;
	private:
		uint32_t m_RendererID;
		
	};

	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(uint32_t* a_Indices, uint32_t a_Count);
		virtual ~OpenGLIndexBuffer();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual uint32_t GetCount() { return m_Count; };

	private:
		uint32_t m_RendererID;
		uint32_t m_Count;
	};
};

