
#include <iostream>
#include <coroutine>


template <class V>
struct value_awaiter{
    V value;
    bool await_ready() {return true; }
    void await_suspend(auto){}
    V await_resume(){return value; }
};

struct taskv{
    struct promise_type{
        std::exception_ptr error;
        std::suspend_never initial_suspend() noexcept { return {}; }
        std::suspend_never final_suspend() noexcept { return {}; }
        void return_void() {}
        taskv get_return_object() { return {}; }
        void unhandled_exception() { error = std::current_exception(); }
    };
};

template <class T>
struct task{
    struct promise_type{
        std::exception_ptr error;
        std::suspend_never initial_suspend() noexcept { return {}; }
        std::suspend_never final_suspend() noexcept { return {}; }
        void return_void() {}
        taskv get_return_object() { return {}; }
        void unhandled_exception() { error = std::current_exception(); }
    };
    V value;
    bool await_ready() {return true; }
    void await_suspend(auto){}
    V await_resume(){return value; }
};


task <int> get_int(){
    co_return 12;
}

taskv co_main(){
    auto ret = co_await get_int();
    
    std::cout << "Value: " << ret << std::endl;
    co_return;
}


int main(){
    try{
        co_main(  );
	    std::cout << "Hello word" << std::endl;
    }
    catch (std::exception& e){
        std::cout << "Error: " << e.what() << std::endl;
    }
}