#pragma once

#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>

namespace logging = boost::log;

#define LOG_TRACE BOOST_LOG_TRIVIAL(debug)
#define LOG_DEBUG BOOST_LOG_TRIVIAL(debug)
#define LOG_INFO  BOOST_LOG_TRIVIAL(info) 
#define LOG_WARNING BOOST_LOG_TRIVIAL(warning) 
#define LOG_ERROR BOOST_LOG_TRIVIAL(error) 
#define LOG_FATAL BOOST_LOG_TRIVIAL(fatal) 


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