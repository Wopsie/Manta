#pragma once
#include "Manta/Renderer/VertexArray.h"

namespace Manta
{
	class OpenGLVertexArray : public VertexArray
	{
	public:
		OpenGLVertexArray();
		virtual ~OpenGLVertexArray();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& a_VertexBuffer) override;
		virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& a_IndexBuffer) override;


		virtual const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const { return m_VertexBuffers; };
		virtual const std::shared_ptr<IndexBuffer>& GetIndexBuffers() const { return m_IndexBuffer; };
		
	private:
		std::vector<std::shared_ptr<VertexBuffer>> m_VertexBuffers;
		std::shared_ptr<IndexBuffer> m_IndexBuffer;
		//std::vector<std::shared_ptr<IndexBuffer>> m_IndexBuffers;
		uint32_t m_RendererID;
	};

}
