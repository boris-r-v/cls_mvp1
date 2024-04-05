#pragma once

#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>

namespace logging = boost::log;

#define LOG_TRACE BOOST_LOG_TRIVIAL(trace)
#define LOG_DEBUG BOOST_LOG_TRIVIAL(debug)
#define LOG_INFO  BOOST_LOG_TRIVIAL(info) 
#define LOG_WARNING BOOST_LOG_TRIVIAL(warning) 
#define LOG_ERROR BOOST_LOG_TRIVIAL(error) 
#define LOG_FATAL BOOST_LOG_TRIVIAL(fatal) 

namespace cls_core::logger{
    void set_severity_trace();
    void set_severity_debug();
    void set_severity_info();
    void set_severity_warning();
    void set_severity_error();
    void set_severity_fatal();
    void set_severity( int severity);
}


/*
#include <iostream>
#include <string_view>

enum LogLevel { DEBUG=0, INFO, WARNING, ERROR, CRITICAL }; 

class Logger{
    public:
        Logger( std::ostream& );
        void log( LogLevel, std::string_view ); 
        void set_level( LogLevel);
    private:
        std::ostream& log_stream_;
        int level_;
        std::string_view lvl2str(LogLevel);
};
extern Logger logger;  

*/