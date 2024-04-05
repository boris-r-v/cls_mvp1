#ifndef _redis_pool_h_define_
#define _redis_pool_h_define_

#include <list>
#include <memory>

#ifndef REDIS_CLUSTER
#include <sw/redis++/co_redis++.h>
#else
#include <sw/redis++/co_redis_cluster.h>
#endif


namespace cls_core
{

#ifndef REDIS_CLUSTER
    typedef std::shared_ptr<sw::redis::CoRedis> redis_t;
#else
    typedef std::shared_ptr<sw::redis::CoRedisCluster> redis_t;
#endif

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

            
    };
} // namespace cls_core









#endif  //_redis_h_define_