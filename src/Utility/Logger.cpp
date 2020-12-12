#include "Logger.h"

const char* LogTypeString[] = {"Debug","Info","Warning","Error"};


Logger::Logger()
{
    logFile.open("log.txt");
    if(!logFile.is_open())
        std::cout <<"Failed to open logfile log.txt\n";
    CoutLog = WARNING;
    FileLog = DEBUG;
}

void Logger::Log(const std::string& str, Logger::LogMode mode)
{
    if((int)mode >= (int)FileLog)
        logFile << "["<<LogTypeString[(int)mode]<<"]: " << str <<"\n";
    if((int)mode >= (int)CoutLog)
        std::cout << "["<<LogTypeString[(int)mode]<<"]: "<<str<<"\n";
}

Logger& Logger::GetInstance(void)
{
    static Logger log;
    return log;
}
