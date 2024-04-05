#include <cls_config.h>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/foreach.hpp>



cls_core::config& cls_core::config::instance() noexcept {
    static config instance__;
    return instance__;
}

cls_core::config& cls_core::config::load( std::string const& path ){
    pt::read_xml( path, ptree_);
    return *this;
}
