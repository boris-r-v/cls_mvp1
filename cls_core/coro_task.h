#ifndef __coro_task__
#define __coro_task__

#include <coroutine>
#include <utility>
#include <exception>
#include <optional>
#include <iostream>
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

namespace cls_core{

    template <class T>
    class Task;

    template <class T>
    class PromiseBase{
        public:
            constexpr std::suspend_never initial_suspend() const noexcept { return {}; }
            constexpr std::suspend_never final_suspend() const noexcept { return {}; }
            void unhandled_exception();

        protected:    
            friend class Task<T>;
            Task<T>* task_;
            void resumeWaitingCoro();
    };
    template <class T>
    class Promise: public PromiseBase<T>{
        public:
            Task<T> get_return_object(); 
            void return_value(auto&& arg);  
    };
    template <>
    class Promise<void>: public PromiseBase<void>{
        public:
            Task<void> get_return_object(); 
            void return_void();
    };
/*----------------------TaskBase---------------------------*/
    template <class T>
    class TaskBase {
        public:
            using promise_type = Promise<T>;
            TaskBase(TaskBase&& other) = default;
            TaskBase(promise_type* promise ):promise_{promise} {}
            void await_suspend(auto h){ handle_ = h; /*handle_ = std::move(h);*/ }

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
                    std::cout << "TaskBase<void>\n"; 
                    promise_->task_ = this;
                    completed_ = other.completed_;
            }
            bool await_ready(){
                return ( completed_ || exception_ );
            }
            void await_resume(){
                if (exception_) std::rethrow_exception( exception_ );
            }
        private:
            friend class Promise<void>;
            bool completed_ = false;    
    };

/*---------------------------impl---------------------*/
    
    template <class T>
    void PromiseBase<T>::unhandled_exception(){ 
        std::cout << "task" << task_ << "\n";
        task_->exception_ = std::current_exception(); 
        resumeWaitingCoro();
    }

    template <class T>
    void PromiseBase<T>::resumeWaitingCoro(){
        if (task_->handle_) task_->handle_.resume();
    }

    template <class T>
    Task<T> Promise<T>::get_return_object(){
        return Task<T>{this};
    }

    template <class T>
    void Promise<T>::return_value(auto&& arg){
        PromiseBase<T>::task_->result_.emplace(std::forward<decltype(arg)>(arg));
        PromiseBase<T>::resumeWaitingCoro();
    }

    inline Task<void> Promise<void>::get_return_object(){ 
        return Task<void>{this}; 
    }
    inline void Promise<void>::return_void(){ 
        task_->completed_ = true; 
        resumeWaitingCoro();
    }


} //cls_core

#endif // __coro_task__