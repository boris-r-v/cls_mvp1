#ifndef __template_cache__
#define __template_cache__

#include <string>
#include <string_view>
#include <unordered_map>
namespace cls_core
{
    class template_cache{
            typedef std::unordered_map <int, std::string> cache_t;
            cache_t cache_;
        public:
            template_cache() = default;
            ~template_cache() = default;
            
            std::string_view get(int id);

            static template_cache& instance();
            
    };

}
#endif// __template_cache__