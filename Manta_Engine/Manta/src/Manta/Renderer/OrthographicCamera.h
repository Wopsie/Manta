#pragma once

#include <glm/glm.hpp>

namespace Manta
{
	class OrthographicCamera
	{
	public:
		OrthographicCamera(float a_Left, float a_Right, float a_Bottom, float a_Top);

		const glm::vec3& GetPosition() const {return m_Position; }
		void SetPosition(const glm::vec3& a_Pos) { m_Position = a_Pos; RecalculateViewMatrix(); }
		//void SetPosition(const glm::vec3& a_Pos) { m_Position = a_Pos; m_IsDirty = true; }

		const float& GetRotation() const { return m_ZRotation; }
		void SetRotation(const float& a_Rot) { m_ZRotation = a_Rot; RecalculateViewMatrix(); }
		//void SetRotation(const float& a_Rot) { m_ZRotation = a_Rot; m_IsDirty = true; }

		const glm::mat4& GetProjectionMatrix() const { return m_ProjMatrix; }
		const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
		const glm::mat4& GetViewProjectionMatrix() const { return m_ViewProjMatrix; }
		
	private:
		glm::mat4 m_ProjMatrix;
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ViewProjMatrix;
		
		glm::vec3 m_Position = { 0.0f,0.0f,0.0f };
		float m_ZRotation = 0.0f;
		bool m_IsDirty = false;

		void RecalculateViewMatrix();
		
	};
}

