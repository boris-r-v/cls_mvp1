#ifndef _redis_pool_h_define_
#define _redis_pool_h_define_

#include <list>
#include <memory>
//#include <sw/redis++/co_redis++.h>
#include <sw/redis++/co_redis_cluster.h>
#include <mutex>

namespace cls_core
{
    //typedef std::shared_ptr<sw::redis::CoRedis> redis_t;
    typedef std::shared_ptr<sw::redis::CoRedisCluster> redis_t;
    class redis_pool{
            std::list <redis_t> list_;  //FIX ME - have to change to lock-free, thread-save queue 
            std::list <redis_t>::iterator next_;
            std::mutex lock_;
            std::shared_ptr<sw::redis::EventLoop> event_loop_;

        public:
            redis_pool();
            static redis_pool& instance();
            void add_conn(std::string const& ip, size_t port );
            redis_t get( );

//            redis_t pop();      //obsolete
//            void push(redis_t); //obsolete
            
    };
} // namespace cls_core









#endif  //_redis_h_define_