#include "TraceGenerator.hpp"
const long long prof::TraceGenerator::m_initTime{ std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count() };
