#pragma once

#include <string>
#include <boost/property_tree/ptree.hpp>
namespace pt = boost::property_tree;

namespace cls_core{
    class config{
            pt::ptree ptree_;
        public:
            static config& instance() noexcept;
            /**
             * Load config file
             *  - Imagine config filename sets as first param in command line: "cls_server config.xml"
             * int main(int argc, char** argv){
             *      ...
             *      cls_core::config::instance().load(argv[1])
             *      ...
             * }
            */
            config& load( std::string const& );
            /**
             * Use folowing version of get to find field data with wxplicit set of type
             * auto bind = cls_core::config::instance().get<std::string>("cls.server_bind");
            */
            template <class T>
            T get(std::string const&);
            
            /**
             * Use folowing version of get to find field data and if data is not exists - use default value
             * Note! default value use to deduct rreturn type
             * auto sev_level = cls_core::config::instance().get("cls.severity_level", 2);
            */
            template <class T>
            T get(std::string const&, T);

            /**
             * Use to fetch children from some node
            */
            template <class T>
            void get_children(std::string const&, T);
    };
}


template <class T>
T cls_core::config::get(std::string const& _key){
    return ptree_.get< T >( _key );
}

template <class T>
T cls_core::config::get(std::string const& _key, T _default){
    return ptree_.get( _key, _default );
}

template <class T>
void cls_core::config::get_children(std::string const& _key, T _array){
    for (auto &x : ptree_.get_child( _key ) ){
        _array.push_back( x.second.data() );
    }
}
