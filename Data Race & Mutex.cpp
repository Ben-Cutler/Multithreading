// thread example
#include <iostream>       // std::cout
#include <mutex>           //std::mutex
#include <thread>         // std::thread
#include <fstream>        //std:: ofstream

std::mutex mu;

void safePrint(std::string message,int key){
    /*

    The safeprint function prevents two threads from competing to use the cout resource. There are two ways to do this:

    mu.lock / mu.unlock : Locks cout from being used by other threads by locking the global mu
    lock_guard // Similar to mu.lock, but it unlocks when it leaves scope.

    */

    std::lock_guard<std::mutex> guard(mu); // Safer than using mu.lock - In the corner case where cout throws an exception
    //mu.lock(); // Prevents data race where the 'first' thread competes with the main thread for cout usage. lock_guard is better though ; Cout can still have a data race with couts called normally
    std::cout << message <<key << std::endl;
    //mu.unlock();
    return;
}

class filePrint {
    /*
    This class solves the data race issue where something outside could use cout, and this prints to a file instead of the terminal
    */
    std::ofstream OFP;
    //std::mutex mu;
    public:
    filePrint(){OFP.open("log.txt");}
    ~filePrint(){OFP.close();}
    void printToFile(std::string msg, int key){
        std::lock_guard<std::mutex> guard(mu);
        OFP << msg <<key << std::endl;
    }
};

void function_1(filePrint& logFile){
    for(int i=0 ; i<100 ; i++){
        logFile.printToFile("From thread : ",i);
        //safePrint("From thread : " ,i);

    }
}

int main()
{
    filePrint logFile;
    std::thread first (function_1,std:: ref(logFile)); // Threads take all args by VALUE so you have to use ref to explicitly pass them by reference

  for (int j=0 ;j>-100 ; --j){
        //safePrint("From main : " , j);
        logFile.printToFile("From main : ",j);
  }
  first.join();




  std::cout << "Goodbye world!" <<std::endl;






  return 0;
}
