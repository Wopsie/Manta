#pragma once

#include <memory>

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace Manta
{
	
	class MANTA_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
		
	};

}

// Core log macros
#define MNT_CORE_TRACE(...) ::Manta::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define MNT_CORE_INFO(...)  ::Manta::Log::GetCoreLogger()->info(__VA_ARGS__)
#define MNT_CORE_WARN(...)  ::Manta::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define MNT_CORE_ERROR(...) ::Manta::Log::GetCoreLogger()->error(__VA_ARGS__)
#define MNT_CORE_FATAL(...) ::Manta::Log::GetCoreLogger()->fatal(__VA_ARGS__)

// Client log macros
#define MNT_TRACE(...)      ::Manta::Log::GetClientLogger()->trace(__VA_ARGS__)
#define MNT_INFO(...)       ::Manta::Log::GetClientLogger()->info(__VA_ARGS__)
#define MNT_WARN(...)       ::Manta::Log::GetClientLogger()->warn(__VA_ARGS__)
#define MNT_ERROR(...)      ::Manta::Log::GetClientLogger()->error(__VA_ARGS__)
#define MNT_FATAL(...)      ::Manta::Log::GetClientLogger()->fatal(__VA_ARGS__)
