#pragma once

namespace Manta
{
	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() {};

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		static VertexBuffer* Create(float* a_Vertices, uint32_t a_Size);
	};

	class IndexBuffer
	{
	public:
		virtual ~IndexBuffer() {};
		
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual uint32_t GetCount() = 0;
		
		static IndexBuffer* Create(uint32_t* a_Indices, uint32_t a_Count);
	};
}