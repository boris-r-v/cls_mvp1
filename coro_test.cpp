#include <coro_task.h>
#include <iostream>

cls_core::Task<int> CoroReturnsTask() {
    
    co_return 200;
}


cls_core::Task<void> void_coro_throw(){
    throw std::runtime_error("void_coro_throw");
    co_return;
}

cls_core::Task<void> co_main(){

    try{
        //auto ret = co_await CoroReturnsTask();
        //std::cout << "CoroReturnsTask result: " << ret << std::endl;
        
        co_await void_coro_throw();
    }
    catch(std::exception& ex){
        std::cout << ex.what() << std::endl;
    }
}


int main(){

    co_main();
//    std::cout << "CoroReturnsTask result: " << CoroReturnsTask() << std::endl;

}
