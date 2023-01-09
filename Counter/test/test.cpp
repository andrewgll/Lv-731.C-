#include <mutex>
#include <future>
#include <vector>
#include <iostream>

std::mutex statsMutex;
std::vector<std::future<void>> futures;
std::vector<std::string> testvec;


void a(std::string filePath, int i){
            std::cout << i <<filePath << '\n'; 
    statsMutex.lock();
    testvec.push_back(filePath);
    statsMutex.unlock();
}

int main(){
    std::string inputPath = "hello";
    std::string file = "world";
    
    std::string path = inputPath + '/' + file;
    int i = 20;
        while(i){     
            std::cout << path << '\n'; 
      futures.push_back(std::async(std::launch::async, [&]
                                             { a(path, i); }));
        i--;
        }

}