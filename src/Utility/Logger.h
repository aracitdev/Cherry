#ifndef LOGGER_H_INCLUDED
#define LOGGER_H_INCLUDED
#include <iostream>
#include <fstream>

class Logger
{
public:

    static Logger Instance;

    enum LogMode
    {
        DEBUG=0,
        INFO,
        WARNING,
        ERROR
    };

    static Logger& GetInstance(void);

    void Log(const std::string& str, LogMode mode);

    LogMode CoutLog;
    LogMode FileLog;


    std::ofstream logFile;
private:


    Logger();
};

#endif // LOGGER_H_INCLUDED
