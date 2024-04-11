
#include <iostream>
#include <coroutine>
#include <unordered_map>
#include <functional>

template <class V>
struct value_awaiter{
    V value;
    bool await_ready() {return true; }
    void await_suspend(auto){}
    V await_resume(){return value; }
};

struct task{
    struct promise_type{
        std::exception_ptr error;
        std::suspend_never initial_suspend() noexcept { return {}; }
        std::suspend_never final_suspend() noexcept { return {}; }
        void return_void() {}
        task get_return_object() { return {}; }
        void unhandled_exception() { error = std::current_exception(); }

        //template <class V>
        //auto await_transform(V v){return value_awaiter{v};}
    };
};

struct io {
    std::unordered_map<int, std::function<void(std::string)> > out;
    void submit(int fd,  auto fun){
        out[fd] = fun;
    }
    void complete(int fd,  std::string value){
        auto it = out.find(fd);
        if (it != out.end()){
            it->second(value);
        }
    }
};
struct async_read{
    io& context;
    int fd;
    std::string value{};
    constexpr bool await_ready() const {return false;}
    void await_suspend(std::coroutine_handle<> h ) {
        context.submit(fd, [this, h](std::string const& line){
            value = line;
            h.resume();
        });

    }
    std::string await_resume() {return value;}
};

task f(io& c) {
/*    std::cout << "Value: "<< co_await value_awaiter{17} << std::endl;
    std::cout << "Value: "<< co_await 27 << std::endl;
    std::cout << "Value: "<< co_await "27--72" << std::endl;
*/
    std::cout << "first: "<< co_await async_read{c, 1} << std::endl;
    std::cout << "second: "<< co_await async_read{c, 1} << std::endl;
}
int main(){
    try{
        io context;
        auto t = f( context );
        (void)t;
        context.complete(1, "first");
        std::cout << "back in main\n";
        context.complete(1, "second");

	    std::cout << "Hello word" << std::endl;
    }
    catch (std::exception& e){
        std::cout << "Error: " << e.what() << std::endl;
    }
}
