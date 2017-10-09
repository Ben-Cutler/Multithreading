#include<iostream>              //std::cout/endl;
#include<vector>                //std::vector
#include<thread>                //std::thread
#include<mutex>                 //std:mutex
#include<stack>                 //std:stack
#include<condition_variable>    //std::condition_variable

std :: stack<int> myStack; // Global stack that gets filled on one function, and emptied in another method
std :: mutex mu; // Mutex locker
std :: condition_variable cond; // Wakes up thread

void fillStack(){
    int counter= 23;
    do{
        --counter;
        std::unique_lock<std::mutex>locker(mu); //Protect the stack from funkyness
        myStack.push(counter);
        locker.unlock(); //Unlock the stack once it has been accessed
        cond.notify_one(); // Notifies waiting threads

        std :: this_thread :: sleep_for(std::chrono::milliseconds(15)); // We have to sleep this, or else the counter will loop to 0 and cause bad things to happen

    }while (counter);
    return;

}


void emptyStack(){
    int data;
    do{
        std::unique_lock<std::mutex>locker(mu); // Again, we protect the stack from funkyness
        cond.wait(locker,[](){return !myStack.empty();} ); // We then wait for the fillstack to give the OK
        data = myStack.top();
        myStack.pop();
        locker.unlock();//We then unlock the stack
        std::cout <<"From Thread 2 "<< data <<std::endl;

    }while(data);

    return;



}
int main(){
    std :: cout << "Hello World" << std::endl;
    std::thread t1(fillStack);
    std::thread t2(emptyStack);

    t1.join();
    t2.join();


    return 0;
}


