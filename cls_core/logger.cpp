#include <logger.h>

/*
#include <ctime> 
#include <fstream> 
#include <iostream> 
#include <sstream> 

Logger logger(std::cout);

Logger::Logger( std::ostream& s):log_stream_(s), level_(-1) {}
    
void Logger::log(LogLevel level, std::string_view message) 
{ 
    if (level_ > level ) 
        return;
    time_t now = time(0); 
    tm* timeinfo = localtime(&now); 
    char timestamp[20]; 
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", timeinfo); 

    std::ostringstream ss;
    ss << "[" << timestamp << "] " << lvl2str(level) << ": " << message << std::endl; 

    log_stream_ << ss.str(); 
}

void Logger::set_level( LogLevel l ){
    level_ = l;
}

std::string_view Logger::lvl2str(LogLevel level) 
{ 
    switch (level) { 
        case DEBUG: 
            return "DEBUG"; 
        case INFO: 
            return "INFO"; 
        case WARNING: 
            return "WARNING"; 
        case ERROR: 
            return "ERROR"; 
        case CRITICAL: 
            return "CRITICAL"; 
        default: 
            return "UNKNOWN"; 
    } 
} 
 
  */