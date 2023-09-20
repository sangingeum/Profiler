#pragma once
#include <string>
#include <fstream>
#include <chrono>
#include <thread>
#include <string_view>
#include <queue>
#include <atomic>
#include <format>
namespace prof {
	// Singleton Profiler
	// RAII style
	class Profiler
	{
	private:
		std::ofstream m_outFile;
		std::queue<std::tuple<>> m_traceQueue;
	public:
		// Times are given in microseconds
		static void sendTrace(const std::string& name, long long duration, long long startTime, size_t threadID) {
			static Profiler profiler;
			profiler.writeTrace(name, duration, startTime, threadID);
		}
	private:
		Profiler(const std::string& fileName = "profile_result.json") {
			m_outFile.open(fileName);
			m_outFile << "{\"traceEvents\":[";
			std::thread traceProcessingThread();
		}
		Profiler(const Profiler&) = delete;
		Profiler& operator=(const Profiler&) = delete;
		~Profiler() {
			long pos = m_outFile.tellp();
			// Erase the last comma
			m_outFile.seekp(pos - 1);
			m_outFile << "]}";
			m_outFile.close();
		}
		void writeTrace(const std::string& name, long long duration, long long startTime, size_t threadID) {
			m_outFile <<  "{" + std::format("\"name\":\"{}\",\"dur\":{},\"ph\":\"X\",\"pid\":0,\"tid\":{},\"ts\":{}", name, duration, threadID, startTime) + "},";
		}
	};
}




