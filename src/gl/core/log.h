#ifndef GFXE_LOG_H
#define GFXE_LOG_H

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

enum LogLevel {
	Debug = 0,
	Info,
	Warning,
	Error,
	Fatal
};

class Logger {
public:
	Logger();
	Logger(std::ostream* output);
	~Logger();

	void print(LogLevel level, const char* file, const char* function, int line, const std::string& msg);

	static Logger& getSingleton() { return logger; }
private:
	std::ostream* m_output;

	static Logger logger;
	static std::ofstream* logFile;
};

#define LOGGER Logger::getSingleton()

template<typename T>
std::string Str(const T& value) {
	std::ostringstream oss;
	oss << value;
	return oss.str();
}

template<typename T, typename ... Args >
std::string Str(const T& value, const Args& ... args) {
	return Str(value) + Str(args...);
}

#define Print(l, ...) LOGGER.print(l, __FILE__, __FUNCTION__, __LINE__, Str(__VA_ARGS__))
#define Log(...) Print(LogLevel::Debug, __VA_ARGS__)
#define LogInfo(...) Print(LogLevel::Info, __VA_ARGS__)
#define LogWarning(...) Print(LogLevel::Warning, __VA_ARGS__)
#define LogError(...) Print(LogLevel::Error, __VA_ARGS__)
#define LogFatal(...) Print(LogLevel::Fatal, __VA_ARGS__)

#endif // GFXE_LOG_H
