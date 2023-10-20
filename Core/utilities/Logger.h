#ifndef LOGGER_H
#define LOGGER_H

#define _CRT_SECURE_NO_WARNINGS

#include <thread>
#include <iostream>
#include <queue>
#include <mutex>
#include <ctime>
#include <string>
#include <chrono>


/// @brief Log system which run on separate thread
///	@brief Should call Logger::init() to initialized log system
/// @brief Use macros: APP_INFO, APP_WARN, APP_ERROR, APP_CRITICAL, format like func printf
class Logger
{
public:
	enum LogLevel {
		INFO,
		WARN,
		ERROR,
		CRITICAL
	};

	struct Log {
		std::string _message;
		LogLevel _level;
		Log(LogLevel level, const char* message) : _message(message), _level(level) {}

		// TODO: handle error formated cases.
		template<typename... Args>
		Log(LogLevel level, const char* message, Args... args) {
			_level = level;
			_message = string_format(message, args...);
		}
	};

	template<typename... Args>
	static void Info(const char* message, Args... args) {
		Logger::instance()->_logHolder.push(Log( INFO, message, args...));
	}

	template<typename... Args>
	static void Warn(const char* message, Args... args) {
		Logger::instance()->_logHolder.push(Log(WARN, message, args...));
	}

	template<typename... Args>
	static void Error(const char* message, Args... args) {
		Logger::instance()->_logHolder.push(Log(ERROR, message, args...));
	}

	template<typename... Args>
	static void Critical(const char* message, Args... args) {
		Logger::instance()->_logHolder.push(Log(CRITICAL, message, args...));
	}

	static void init();
	static void clean();

private:
	Logger(const Logger& obj) = delete;
	void operator=(const Logger& obj) = delete;
	Logger() = default;
	static Logger* instance() {
		if (_instance == NULL) {
			_instance = new Logger();
		}
		return _instance;
	}

	void run();
	static void print(Log &log);

	static Logger* _instance;
	std::thread* _logThread;
	std::atomic<bool> _stopPrint = false;
	std::queue<Log> _logHolder;

	// just copy from https://learn.microsoft.com/en-us/answers/questions/813614/how-to-printf-to-std-string-by-using-of-a-function
	// TODO should convert to C string for better performance, memory
	template< typename... Args >
	inline static std::string string_sprintf(const char* format, Args... args) {
		int length = std::snprintf(nullptr, 0, format, args...);
		_ASSERT(length >= 0);

		char* buf = new char[length + 1];
		std::snprintf(buf, length + 1, format, args...);

		std::string str(buf);
		delete[] buf;
		return str;
	}

	template<typename ... Args>
	inline static std::string string_format(const std::string& format, Args ... args)
	{
		int size_s = std::snprintf(nullptr, 0, format.c_str(), args ...) + 1; // Extra space for '\0'  
		if (size_s <= 0) { throw std::runtime_error("Error during formatting."); }
		auto size = static_cast<size_t>(size_s);
		std::unique_ptr<char[]> buf(new char[size]);
		std::snprintf(buf.get(), size, format.c_str(), args ...);
		return std::string(buf.get(), buf.get() + size - 1); // We don't want the '\0' inside  
	}
};

#if APP_ENABLE_APP_LOGGER
	#define APP_INFO(...)		::Logger::Info(__VA_ARGS__)
	#define APP_WARN(...)		::Logger::Warn(__VA_ARGS__)
	#define APP_ERROR(...)		::Logger::Error(__VA_ARGS__)
	#define APP_CRITICAL(...)	::Logger::Critical(__VA_ARGS__)
#else
	#define APP_INFO(...)		
	#define APP_WARN(...)		
	#define APP_ERROR(...)		
	#define APP_CRITICAL(...)	
#endif

#endif