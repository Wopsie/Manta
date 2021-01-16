#pragma once
#include "Manta/Renderer/Shader.h"
#include <string>

namespace Manta
{
	class OpenGLShader : public Manta::Shader
	{
	public:
		OpenGLShader(const std::string& a_VertexSrc, const std::string& a_FragmentSrc);
		~OpenGLShader();
		
		virtual void Bind() const override;
		virtual void Unbind() const override;
	private:
		uint32_t m_RendererID;
	};
}
