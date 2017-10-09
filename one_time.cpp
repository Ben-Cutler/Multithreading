// thread example
#include <iostream>       // std::cout
#include <mutex>           //std::mutex
#include <thread>         // std::thread

std::mutex mu;

void printsStuff(std::once_flag& _f,std::string msg){
    // Allows a function that runs on many threads to execute one operation only once.
    // Prevents threads from stepping on each others toes'
    //
    for (int i=0;i<100 ; i++){
        std::call_once(_f,[&](){std::cout << "FIRST ";}); // Though this function is called by both main and thread t1 - It only executes the print once.
        mu.lock();
        std::cout <<"From "<<msg << " Number " <<i << std::endl;
        mu.unlock();

    }
}



int main(){
    std::once_flag Flag;
    std::thread t1(printsStuff,std::ref(Flag),"Thread");

    printsStuff(Flag,"Main");
    //std::cout << "Hello World" << std::endl;

    t1.join();


    return 0;
}
