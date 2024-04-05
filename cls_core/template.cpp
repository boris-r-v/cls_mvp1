#include <template.h>
#include <stdexcept>
#include <redis_pool.h>

using namespace cls_core;

std::string_view template_cache::get(int id)
{
/*
    auto fnd = cache_.find(id);
    if (cache_.end() != fnd) 
        return fnd->second;
*/

    throw std::logic_error ("template not found") ;
}

template_cache& template_cache::instance(){
    static template_cache instance_;
    return instance_;
}