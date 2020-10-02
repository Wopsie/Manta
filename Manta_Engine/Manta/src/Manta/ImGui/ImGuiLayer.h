#pragma once

#include "Manta/Layer.h"

namespace Manta
{
	class MANTA_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnAttach();
		void OnDetach(); 
		void OnUpdate();
		void OnEvent(Event& event);

	private:
		float m_Time = 0.0f;
		
	};


	
}


