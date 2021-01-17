#pragma once
#include <vector>
#include <string>
namespace Manta
{
	enum class ShaderDataType
	{
		NONE = 0,
		FLOAT,
		FLOAT2,
		FLOAT3,
		FLOAT4,
		MAT3,
		MAT4,
		INT,
		INT2,
		INT3,
		INT4,
		BOOL,
	};

	static uint32_t ShaderDataTypeSize(ShaderDataType a_Type)
	{
		switch(a_Type)
		{
			case ShaderDataType::FLOAT:		return 4;
			case ShaderDataType::FLOAT2:	return 4 * 2;
			case ShaderDataType::FLOAT3:	return 4 * 3;
			case ShaderDataType::FLOAT4:	return 4 * 4;
			case ShaderDataType::MAT3:		return 4 * 3 * 3;
			case ShaderDataType::MAT4:		return 4 * 4 * 4;
			case ShaderDataType::INT:		return 4;
			case ShaderDataType::INT2:		return 4 * 2;
			case ShaderDataType::INT3:		return 4 * 3;
			case ShaderDataType::INT4:		return 4 * 4;
			case ShaderDataType::BOOL:		return 1;
		}

		MNT_CORE_ASSERT(false, "Unknown shader datatype");
		return 0;
	}
	
	struct BufferElement
	{
		std::string m_Name;
		ShaderDataType m_Type;
		uint32_t m_Size;
		uint32_t m_Offset;
		bool m_Normalized = false;

		BufferElement() {};
		
		BufferElement(ShaderDataType a_Type, const std::string& a_Name, bool a_Normalized = false)
			: m_Name(a_Name), m_Type(a_Type), m_Size(ShaderDataTypeSize(a_Type)), m_Offset(0), m_Normalized(a_Normalized)
		{
		}

		uint32_t GetComponentCount() const
		{
			switch (m_Type)
			{
				case ShaderDataType::FLOAT:		return 1;
				case ShaderDataType::FLOAT2:	return 2;
				case ShaderDataType::FLOAT3:	return 3;
				case ShaderDataType::FLOAT4:	return 4;
				case ShaderDataType::MAT3:		return 3 * 3;
				case ShaderDataType::MAT4:		return 4 * 4;
				case ShaderDataType::INT:		return 1;
				case ShaderDataType::INT2:		return 2;
				case ShaderDataType::INT3:		return 3;
				case ShaderDataType::INT4:		return 4;
				case ShaderDataType::BOOL:		return 1;
			}
			
			MNT_CORE_ASSERT(false, "Unknown Shader type element count");
			return 0;
		}
		
	};
	
	class BufferLayout
	{
	public:
		BufferLayout() {};
		
		BufferLayout(const std::initializer_list<BufferElement>& a_Elements)
			: m_Elements(a_Elements)
		{
			CalculateOffsetsAndStride();
		};

		inline uint32_t GetStride() const { return m_Stride; }
		
		inline const std::vector<BufferElement>& GetElements() const { return m_Elements; }

		std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
		std::vector<BufferElement>::iterator end() { return m_Elements.end(); }
		std::vector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); }
		std::vector<BufferElement>::const_iterator end() const { return m_Elements.end(); }
		
	private:
		void CalculateOffsetsAndStride()
		{
			uint32_t offset = 0;
			m_Stride = 0;
			for (auto& element : m_Elements )
			{
				element.m_Offset = offset;
				offset += element.m_Size;
				m_Stride += element.m_Size;
			}
		}
		
		std::vector<BufferElement> m_Elements;
		uint32_t m_Stride = 0;
	};
	
	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() {};

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual const BufferLayout& GetLayout() const = 0;
		virtual void SetLayout(const BufferLayout& a_Layout) = 0;
		
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