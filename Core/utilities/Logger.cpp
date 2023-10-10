#include "Logger.h"

Logger* Logger::_instance = Logger::instance();

std::mutex _m;

void Logger::clean()
{
	Logger::instance()->_stopPrint = true;
	if (Logger::instance()->_logThread != NULL) {
		if (Logger::instance()->_logThread->joinable()) {
			Logger::instance()->_logThread->join();
		}
		delete Logger::instance()->_logThread;
	}
	if (Logger::instance()->_instance != NULL)
		delete _instance;
	std::cout << "Clean log thread!\n";
}

void Logger::init()
{
	Logger* l = Logger::instance();
	Logger::instance()->_logThread = new std::thread(&Logger::run, l);
}


void Logger::run()
{
	std::cout << "Start log thread!\n";
	std::queue<Log>* logPtr = &Logger::instance()->_logHolder;
	while (!instance()->_stopPrint) {
		if (logPtr->size() > 0) {
			print(logPtr->front());
			logPtr->pop();
		}
	}
}

void Logger::print(Log& log)
{
	static std::time_t t = std::time(0);
	static std::tm* now = localtime(&t);
	printf("\033[1;32m[%d:%d:%d %d-%d-%d] ", 
		now->tm_hour, now->tm_min, now->tm_sec,
		now->tm_mday, now->tm_mon + 1, now->tm_year + 1900);
	switch (log._level)
	{
	case INFO:
		printf("\033[1;36m[INFO]\033[0;0m: ");
		break;
	case WARN:
		printf("\033[1;33m[WARNING]\033[0;0m: ");
		break;
	case ERROR:
		printf("\033[1;31m[ERROR]\033[0;0m: ");
		break;
	case CRITICAL:
		printf("\033[1;31m[CRITICAL]\033[0;0m: ");
		break;
	}
	printf("%s\n", log._message.c_str());
}

