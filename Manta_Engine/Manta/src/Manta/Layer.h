#pragma once

#include "Manta/Core.h"
#include "Manta/Core/Timestep.h"
#include "Manta/Events/Event.h"

namespace Manta
{
	class MANTA_API Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(Timestep a_TS) {}
		virtual void OnImGuiRender() {}
		virtual void OnEvent(Event& event) {}

		inline const std::string& GetName() const { return m_DebugName; }
	protected:
		std::string m_DebugName;
	};
};
