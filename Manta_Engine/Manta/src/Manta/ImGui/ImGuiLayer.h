#pragma once

#include "Manta/Layer.h"

#include "Manta/Events/ApplicationEvent.h"
#include "Manta/Events/KeyEvent.h"
#include "Manta/Events/MouseEvent.h"

namespace Manta
{
	class MANTA_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();
	private:
		
		float m_Time = 0.0f;
		
	};


	
}


