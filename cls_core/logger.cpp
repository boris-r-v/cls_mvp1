#include <logger.h>

void cls_core::logger::set_severity_trace(){
    logging::core::get()->set_filter( logging::trivial::severity >= logging::trivial::trace );
    LOG_TRACE << "Change severity log level to TRACE";
}
void cls_core::logger::set_severity_debug(){
    logging::core::get()->set_filter( logging::trivial::severity >= logging::trivial::debug );
    LOG_DEBUG << "Change severity log level to DEBUG";
}
void cls_core::logger::set_severity_info(){
    logging::core::get()->set_filter( logging::trivial::severity >= logging::trivial::info );
    LOG_INFO << "Change severity log level to INFO";
}
void cls_core::logger::set_severity_warning(){
    logging::core::get()->set_filter( logging::trivial::severity >= logging::trivial::warning );
    LOG_WARNING << "Change severity log level to WARNING";
}
void cls_core::logger::set_severity_error(){
    logging::core::get()->set_filter( logging::trivial::severity >= logging::trivial::error );
    LOG_ERROR << "Change severity log level to ERROR";
}
void cls_core::logger::set_severity_fatal(){
    logging::core::get()->set_filter( logging::trivial::severity >= logging::trivial::fatal );
    LOG_FATAL << "Change severity log level to FATAL";
}   

void cls_core::logger::set_severity( int severity){

    switch( severity ){
        case 0: //cls_gen::SeverityEnum::trace:
            cls_core::logger::set_severity_trace();
            break;
        case 1: //cls_gen::SeverityEnum::debug:
            cls_core::logger::set_severity_debug();
            break;
        case 2: //cls_gen::SeverityEnum::info:
            cls_core::logger::set_severity_info();
            break;
        case 3: //cls_gen::SeverityEnum::warning:
            cls_core::logger::set_severity_warning();
            break;
        case 4: //cls_gen::SeverityEnum::error:
            cls_core::logger::set_severity_error();
            break;
        case 5: //cls_gen::SeverityEnum::fatal:
            cls_core::logger::set_severity_fatal();
            break;
        default:
            LOG_FATAL << "Unknown severity log level code: <" << severity <<">";
            cls_core::logger::set_severity_error();
    }
}

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