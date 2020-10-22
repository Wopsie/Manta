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

		void OnAttach();
		void OnDetach(); 
		void OnUpdate();
		void OnEvent(Event& event);

	private:
		bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
		bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
		bool OnMouseMovedEvent(MouseMovedEvent& e);
		bool OnMouseScrolledEvent(MouseScrolledEvent& e);
		bool OnKeyPressedEvent(KeyPressedEvent& e);
		bool OnKeyReleasedEvent(KeyReleasedEvent& e);
		bool OnKeyTypedEvent(KeyTypedEvent& e);
		bool OnWindowResizeEvent(WindowResizeEvent& e);
		
		
		float m_Time = 0.0f;
		
	};


	
}


