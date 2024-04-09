#ifndef __coro_task__
#define __coro_task__

#include <coroutine>


namespace cls_core{
/*    
    struct promise;
    struct Task: std::coroutine_handle<promise>
    {
        using promise_type = cls_core::promise;
    };
    struct promise{
            Task get_return_object() { return Task{}; }
            std::suspend_never initial_suspend() noexcept { return {}; }
            std::suspend_never final_suspend() noexcept { return {}; }
            void return_void() {}
            void unhandled_exception() {} 
    };
*/    
/*----------------PromiseBase------------------------------*/
    template <class T>
    class Task;
    template <class T>
    class PromiseBase{
        public:
            constexpr std::suspend_never initial_suspend() const noexcept { return {}; }
            constexpr std::suspend_never final_suspend() const noexcept { return {}; }
            void unhandled_exception(){ task_->exception_ = std::current_exception(); }

        protected:    
            friend class Task<T>;
            Task<T>* task_;
    };
    template <class T>
    class Promise: public PromiseBase<T>{
        public:
            Task<T> get_return_object();  //{return Task<T>{this};}
            void return_value(auto&& arg);  //{PromiseBase<T>::task_->result_.emplace(std::forward<decltype(arg)>(arg));}
    };
    template <>
    class Promise<void>: public PromiseBase<void>{
        public:
            Task<void> get_return_object(); //{ return Task<void>{this}; }
            void return_void(); //{}
    };
/*----------------------TaskBase---------------------------*/
    template <class T>
    class TaskBase{
        public:
            using promise_type = Promise<T>;
            TaskBase(TaskBase&& other) = default;
            TaskBase(promise_type* promise ):promise_{promise} {}

            void await_suspend(std::coroutine_handle<> h){ handle_ = h; /*handle_ = std::move(h);*/ }

        protected:
            template <class TT>
            friend class PromiseBase;

            promise_type* promise_;
            std::exception_ptr exception_;
            std::coroutine_handle<> handle_;
    };
    template <class T>
    class Task: public TaskBase<T> {
        public:
            using TaskBase<T>::TaskBase;
            Task(Task<T>&& other): 
                TaskBase<T>(static_cast<TaskBase<T>&&>(other)){
                    TaskBase<T>::promise_->task_ = this;
                    result_ = std::move(other.result_);
            }

            bool await_ready(){ 
                return(result_ || TaskBase<T>::exception_); 
            }

            T await_resume(){
                if (TaskBase<T>::exception_) std::rethrow_exception(TaskBase<T>::exception_);
                return std::move(*result_); 
            }

        private:
            friend class Promise<T>;
            std::optional<T> result_;
    };
    template <>
    class Task<void>: public TaskBase<void>{
        public:
            using TaskBase<void>::TaskBase;
            Task(Task<void>&& other):
                TaskBase<void>(static_cast<TaskBase<void>&& >(other)){
                    promise_->task_ = this;
                    completed_ = other.completed_;
            }
            bool await_ready(){
                return ( completed_ || exception_ );
            }
            bool await_resume(){
                if (exception_) std::rethrow_exception( exception_ );
            }
        private:
            friend class Promise<void>;
            bool completed_ = false;    
    };
} //cls_core

template <class T>
cls_core::Task<T> cls_core::Promise<T>::get_return_object(){
    return Task<T>{this};
}

template <class T>
void cls_core::Promise<T>::return_value(auto&& arg){
    PromiseBase<T>::task_->result_.emplace(std::forward<decltype(arg)>(arg));
}

inline cls_core::Task<void> cls_core::Promise<void>::get_return_object(){ 
    return Task<void>{this}; 
}
inline void cls_core::Promise<void>::return_void(){ 
    task_->completed_ = true; 
}



#endif // __coro_task__