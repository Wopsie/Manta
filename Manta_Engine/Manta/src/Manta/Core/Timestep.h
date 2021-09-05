#pragma once

namespace Manta 
{
	class Timestep
	{
	public:
		Timestep(float a_Time = 0.0f) 
			: m_Time(a_Time)
		{
		}

		operator float() const { return m_Time; }

		float GetSeconds() const { return m_Time; }
		float GetMilliseconds() const { return m_Time * 1000; }
	private:
		float m_Time;
	};
}