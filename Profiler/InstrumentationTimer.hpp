#pragma once
#include "Profiler.hpp"
#include <chrono>

// InstrumentationTimer
// RAII style
namespace prof {
	class InstrumentationTimer {
	private:
		std::chrono::steady_clock::time_point m_start;
		std::string_view m_name;
		static const long long m_initTime;
	public:
		InstrumentationTimer(std::string_view name)
			: m_start(std::chrono::high_resolution_clock::now()), m_name(name) {}
		~InstrumentationTimer() {
			// Get times in microseconds
			auto startTime = std::chrono::duration_cast<std::chrono::microseconds>(m_start.time_since_epoch()).count();
			auto endTime = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
			// Get Thread id
			auto threadID = std::hash<std::thread::id>()(std::this_thread::get_id());
			// Process Trace
			Profiler::processTrace(m_name, endTime - startTime, startTime - m_initTime, threadID);
		}
	};
}


// Define macros for profiling
// Set PROFILE to 1 if you want to profile your code
// Set it to 0 otherwise
#define PROFILE 1
#if PROFILE
#define PROFILE_SCOPE(name) prof::InstrumentationTimer tracer##__LINE__(name)
#else
#define PROFILE_SCOPE(name)
#endif
#define PROFILE_FUNCTION() PROFILE_SCOPE(__FUNCSIG__)