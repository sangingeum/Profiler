#pragma once
#include <fstream>
#include <format>
#include <string_view>

namespace prof {
	// Singleton Profiler
	// RAII style
	class Profiler
	{
	private:
		std::ofstream m_outFile;
	public:
		// Times are given in microseconds
		static void processTrace(std::string_view name, long long duration, long long startTime, size_t threadID) {
			static Profiler profiler;
			profiler.writeTrace(name, duration, startTime, threadID);
		}
	private:
		Profiler(const std::string& fileName = "profile_result.json") {
			m_outFile.open(fileName);
			m_outFile << "{\"traceEvents\":[";
		}
		Profiler(const Profiler&) = delete;
		Profiler& operator=(const Profiler&) = delete;
		~Profiler() {
			size_t pos = m_outFile.tellp();
			// Erase the last comma
			m_outFile.seekp(pos - 1);
			m_outFile << "]}";
			m_outFile.close();
		}
		void writeTrace(std::string_view name, long long duration, long long startTime, size_t threadID) {
			m_outFile <<  "{" + std::format("\"name\":\"{}\",\"dur\":{},\"ph\":\"X\",\"pid\":0,\"tid\":{},\"ts\":{}", name, duration, threadID, startTime) + "},";
		}
	};
}




