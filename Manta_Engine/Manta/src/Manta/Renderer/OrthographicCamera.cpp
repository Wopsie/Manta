#include "mntpch.h"
#include "OrthographicCamera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Manta
{
	
	Manta::OrthographicCamera::OrthographicCamera(float a_Left, float a_Right, float a_Bottom, float a_Top)
		: m_ProjMatrix(glm::ortho(a_Left, a_Right, a_Bottom, a_Top, -1.0f, 1.0f)), m_ViewMatrix(1.0f)
	{
		m_ViewProjMatrix = m_ProjMatrix * m_ViewMatrix;
	}

	void OrthographicCamera::RecalculateViewMatrix()
	{
		glm::mat4 transformMat = glm::translate(glm::mat4(1.0f), m_Position) * glm::rotate(glm::mat4(1.0f), glm::radians(m_ZRotation), glm::vec3(0, 0, 1));
		m_ViewMatrix = glm::inverse(transformMat);
		m_ViewProjMatrix = m_ProjMatrix * m_ViewMatrix;
	}
}
