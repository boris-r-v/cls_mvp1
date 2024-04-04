#ifndef __coro_task__
#define __coro_task__

#include <coroutine>
#include <unordered_map>

namespace cls_core{
    
    struct promise;
    struct Task: std::coroutine_handle<promise>
    {
        using promise_type = cls_core::promise;
    };
    struct promise{
            std::exception_ptr exception_;
            Task get_return_object() { return Task{}; }
            std::suspend_never initial_suspend() noexcept { return {}; }
            std::suspend_never final_suspend() noexcept { return {}; }
            void return_void() {}
            void unhandled_exception() { exception_ = std::current_exception(); std::cout <<"exception\n"; } 
    };




} //cls_core
#endif // __coro_task__